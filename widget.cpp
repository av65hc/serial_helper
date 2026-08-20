#include "widget.h"
#include "ui_widget.h"
#include "tipdialog.h"
#include <QDebug>
#include <QtMath>
#include "qcustomplot.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setPen(QPen(QColor(0,160,255),1.5));
    ui->customplot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customplot->xAxis->setLabel("采样序号");
    ui->customplot->yAxis->setLabel("温度测量值");
    ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    head_char = "";
    last_char = "";

    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, [this](){ head_char = ui->lineEdit_2->text(); });
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, [this](){ last_char = ui->lineEdit_3->text(); });

    my_serial = new QSerialPort;
    my_serial->setPortName("COM10");
    my_serial->setBaudRate(QSerialPort::Baud115200);
    my_serial->setDataBits(QSerialPort::Data8);
    my_serial->setParity(QSerialPort::NoParity);
    my_serial->setStopBits(QSerialPort::OneStop);
    my_serial->setFlowControl(QSerialPort::NoFlowControl);
    connect(my_serial, &QSerialPort::readyRead, this, &Widget::show_text);
}

Widget::~Widget()
{
    delete ui;
    delete my_serial;
}

void Widget::on_pushButton_clicked()
{
    QByteArray head = head_char.toUtf8();
    QByteArray last = last_char.toUtf8();
    QByteArray payload;
    QString info = ui->lineEdit->text();
    if(ui->Hex_send->isChecked()){
        payload = QByteArray::fromHex(info.toLatin1());
    }
    else{
        payload = info.toUtf8();
    }
    QByteArray frame = head + payload + last;
    quint16 crc = crc_cal(frame);
    frame.append(char(crc & 0xFF));
    frame.append(char(crc >> 8));

    my_serial->write(frame);
}

void Widget::on_pushButton_2_clicked()
{
    if (my_serial->isOpen()) {
        my_serial->close();
        qDebug() << "已关闭";
        ui->pushButton_2->setText("打开串口");
        return;
    }

    QString serial_name = ui->serial->text();
    int serial_baud = ui->baudrate->currentText().toInt();
    int serial_parity = ui->parity->currentIndex();
    int serial_databit = ui->databit->currentText().toInt();
    int serial_stopbit = ui->stopbit->currentIndex();

    if (serial_name.isEmpty()) {
        dialog_show("未输入串口号！");
        return;
    }

    my_serial->setPortName(serial_name);

    switch (serial_baud) {
    case 9600:   my_serial->setBaudRate(QSerialPort::Baud9600);   break;
    case 19200:  my_serial->setBaudRate(QSerialPort::Baud19200);  break;
    case 38400:  my_serial->setBaudRate(QSerialPort::Baud38400);  break;
    case 57600:  my_serial->setBaudRate(QSerialPort::Baud57600);  break;
    case 115200: my_serial->setBaudRate(QSerialPort::Baud115200); break;
    }

    switch (serial_parity) {
    case 0: my_serial->setParity(QSerialPort::NoParity);   break;
    case 1: my_serial->setParity(QSerialPort::OddParity);  break;
    case 2: my_serial->setParity(QSerialPort::EvenParity); break;
    }

    switch (serial_databit) {
    case 5: my_serial->setDataBits(QSerialPort::Data5); break;
    case 6: my_serial->setDataBits(QSerialPort::Data6); break;
    case 7: my_serial->setDataBits(QSerialPort::Data7); break;
    case 8: my_serial->setDataBits(QSerialPort::Data8); break;
    }

    switch (serial_stopbit) {
    case 0: my_serial->setStopBits(QSerialPort::OneStop);        break;
    case 1: my_serial->setStopBits(QSerialPort::OneAndHalfStop); break;
    case 2: my_serial->setStopBits(QSerialPort::TwoStop);        break;
    }

    my_serial->open(QIODevice::ReadWrite);
    if (my_serial->isOpen()) {
        ui->pushButton_2->setText("关闭串口");
        qDebug() << "已打开";
    } else {
        ui->pushButton_2->setText("打开串口");
        qDebug() << "串口打开失败";
        dialog_show("串口打开失败：" + my_serial->errorString());
    }
}

void Widget::show_text()
{
    m_buffer.append(my_serial->readAll());
    QByteArray head = head_char.toUtf8();
    QByteArray last = last_char.toUtf8();

    if (head.isEmpty() || last.isEmpty()) {
        if (!m_buffer.isEmpty()) {
            hex_checked(m_buffer);
            m_buffer.clear();
        }
        return;
    }

    while (true) {
        int start = m_buffer.indexOf(head);
        if (start == -1) break;

        int end = m_buffer.indexOf(last, start + head.size());
        if (end == -1) break;

        int frameEnd = end + last.size();
        if (m_buffer.size() < frameEnd + 2) break;

        QByteArray frame = m_buffer.mid(start, frameEnd - start);
        quint16 recvCrc = (quint8)m_buffer.at(frameEnd)
                        | ((quint8)m_buffer.at(frameEnd + 1) << 8);
        quint16 calcCrc = crc_cal(frame);

        if (recvCrc == calcCrc) {
            QByteArray data = m_buffer.mid(start + head.size(),
                                           end - start - head.size());
            QString show_data = QString::fromUtf8(data);
            hex_checked(data);
            m_x.append(m_index++);
            m_y.append(show_data.toFloat());
            if(m_x.size()>max_length){
                m_x.remove(0);
                m_y.remove(0);
            }
            ui->customplot->graph(0)->setData(m_x,m_y);
            ui->customplot->graph(0)->rescaleAxes();
            ui->customplot->replot();
        } else {
            qDebug() << "CRC 校验失败，丢弃一帧";
        }

        m_buffer.remove(0, frameEnd + 2);
    }
}

void Widget::dialog_show(QString text)
{
    TipDialog dialog(this);
    dialog.set_text(text);
    dialog.exec();
}

// void Widget::on_timer_send()
// {
//     if (!my_serial->isOpen())
//         return;

//     static double phase = 0.0;
//     double temp = 25.0 + 5.0 * qSin(phase);
//     phase += 0.3;

//     QByteArray head = head_char.toUtf8();
//     QByteArray last = last_char.toUtf8();

//     QString data = QString::number(temp, 'f', 2);

//     QByteArray frame = head + data.toUtf8() + last;
//     quint16 crc = crc_cal(frame);
//     frame.append(char(crc & 0xFF));
//     frame.append(char(crc >> 8));

//     my_serial->write(frame);
// }

void Widget::on_pushButton_clear_clicked()
{
    ui->textEdit->clear();
    m_buffer.clear();
    m_x.clear();
    m_y.clear();
    m_index = 0;
    ui->customplot->graph(0)->setData(m_x, m_y);
    ui->customplot->graph(0)->rescaleAxes();
    ui->customplot->replot();
}

void Widget::hex_checked(QByteArray &data){
    bool is_checked = ui->Hex_rec->isChecked();
    QString show_info = nullptr;
    if(is_checked){
        show_info= data.toHex(' ');
    }
    else{
        show_info = QString::fromUtf8(data);
    }
    ui->textEdit->append(show_info);
}

quint16 Widget::crc_cal(const QByteArray &data)
{
    quint16 crc = 0xFFFF;
    for (auto byte : data) {
        crc ^= (quint8)byte;
        for (int i = 0; i < 8; i++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void Widget::on_Hex_send_checkStateChanged(const Qt::CheckState &arg1)
{
    QString text = ui->lineEdit->text();
    QString show_text;
    QByteArray raw;
    if(text.isEmpty()) return;
    if(arg1 == Qt::CheckState::Checked){
        raw = text.toUtf8();
        show_text = raw.toHex(' ');
    }
    else{
        raw = QByteArray::fromHex(text.toLatin1());
        show_text = QString::fromUtf8(raw);
    }
    ui->lineEdit->setText(show_text);
}

