#include "widget.h"
#include "ui_widget.h"
#include "tipdialog.h"
#include <QDebug>
#include <QtMath>
#include <QSerialPortInfo>

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

    cir_send = new QTimer(this);
    cir_send->setInterval(1000);
    cir_send->start();
    connect(cir_send,&QTimer::timeout,this,&Widget::send_cir);
    connect(ui->cycle_time,&QLineEdit::textChanged,this,&Widget::on_cycle_time_textChanged);
    m_portCheckTimer = new QTimer(this);
    m_portCheckTimer->setInterval(500);
    connect(m_portCheckTimer,&QTimer::timeout,this,&Widget::checkSerialPortAvailability);
    m_portCheckTimer->start();

    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, [this](){ head_char = ui->lineEdit_2->text(); });
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, [this](){ last_char = ui->lineEdit_3->text(); });

    my_serial = new QSerialPort(this);
    my_serial->setPortName("COM10");
    my_serial->setBaudRate(QSerialPort::Baud115200);
    my_serial->setDataBits(QSerialPort::Data8);
    my_serial->setParity(QSerialPort::NoParity);
    my_serial->setStopBits(QSerialPort::OneStop);
    my_serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(my_serial, &QSerialPort::readyRead, this, &Widget::show_text);

    connect(my_serial,&QSerialPort::errorOccurred,this,[this](QSerialPort::SerialPortError err){
        if(err != QSerialPort::NoError)
        {
            QString errMsg = my_serial->errorString();
            dialog_show("串口发生错误：" + errMsg);
            if(my_serial->isOpen())
                my_serial->close();
            ui->pushButton_2->setText("打开串口");
        }
    });
}

Widget::~Widget()
{
    if(my_serial->isOpen())
        my_serial->close();
    delete ui;
}

void Widget::send_cir()
{
    if(ui->timeout_send->checkState()==Qt::Unchecked)
        return;
    if(!my_serial->isOpen())
    {
        qDebug()<<"定时发送：串口未打开，跳过发送";
        return;
    }
    on_pushButton_clicked();
}

void Widget::on_cycle_time_textChanged(const QString &arg1)
{
    bool ok;
    int ms = arg1.toInt(&ok);
    if(!ok || ms <=0)
    {
        ms = 1000;
    }
    cir_send->setInterval(ms);
}


void Widget::on_pushButton_clicked()
{
    if(!my_serial->isOpen())
    {
        dialog_show("串口未打开，无法发送");
        return;
    }
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
    // 溢出：丢弃前面旧数据，不要直接clear
    if(m_buffer.size() > m_maxBufferSize)
    {
        int dropLen = m_buffer.size() - m_maxBufferSize;
        m_buffer.remove(0, dropLen);
        qDebug()<<"接收缓冲区溢出，丢弃前面"<<dropLen<<"字节";
    }

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

        int frameEnd = end + last.size(); // last结束之后的位置
        // 判断：必须还有完整2字节CRC
        if (m_buffer.size() < frameEnd + 2) break;

        // ==========修复mid第二个参数：长度 frameEnd‑start ==========
        QByteArray frame = m_buffer.mid(start, frameEnd - start);

        quint16 recvCrc = (quint8)m_buffer.at(frameEnd)
                          | ((quint8)m_buffer.at(frameEnd + 1) << 8);

        quint16 calcCrc = crc_cal(frame);
        if (recvCrc == calcCrc) {
            QByteArray data = m_buffer.mid(start + head.size(),
                                           end - start - head.size());
            QString show_data = QString::fromUtf8(data);
            hex_checked(data);
            bool ok = false;
            double val = show_data.toFloat(&ok);
            if(ok)
            {
                m_x.append(m_index++);
                m_y.append(val);
                m_times.append(QDateTime::currentDateTime());
                if(m_x.size()>max_length){
                    m_x.remove(0);
                    m_y.remove(0);
                }
                ui->customplot->graph(0)->setData(m_x,m_y);
                ui->customplot->graph(0)->rescaleAxes();
                ui->customplot->replot();
            }
            else
            {
                qDebug()<<"有效负载不是合法浮点数："<<show_data;
            }
        } else {
            qDebug() << "CRC 校验失败，丢弃一帧";
        }
        // ==========修复：从start位置删除整帧，不是从0删除 ==========
        int totalFrameLen = frameEnd + 2 - start;
        m_buffer.remove(start, totalFrameLen);
    }
}

void Widget::checkSerialPortAvailability()
{
    if (!my_serial->isOpen())
        return;
    QString portName = my_serial->portName();
    bool portExists = false;
    const auto ports = QSerialPortInfo::availablePorts();
    for (const auto &info : ports) {
        if (info.portName() == portName) {
            portExists = true;
            break;
        }
    }
    if (!portExists) {
        my_serial->close();
        ui->pushButton_2->setText("打开串口");
        dialog_show("USB串口设备已移除，连接断开");
    }
}

void Widget::dialog_show(QString text)
{
    TipDialog dialog(this);
    dialog.set_text(text);
    dialog.exec();
}

void Widget::on_pushButton_clear_clicked()
{
    ui->textEdit->clear();
    m_buffer.clear();
    m_x.clear();
    m_y.clear();
    m_times.clear();
    m_index = 0;
    ui->customplot->graph(0)->setData(m_x, m_y);
    ui->customplot->graph(0)->rescaleAxes();
    ui->customplot->replot();
}

void Widget::hex_checked(QByteArray &data){
    bool is_checked = ui->Hex_rec->isChecked();
    QString show_info;
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
    Q_UNUSED(arg1);

}

void Widget::on_btnExportCsv_clicked()
{
    // 1. 空数据判断
    if (m_x.isEmpty() || m_y.isEmpty()) {
        dialog_show("没有可导出的温度数据，请先采集数据");
        return;
    }

    // 2. 弹出保存对话框，默认文件名带时间戳
    QString defaultName = QString("温度数据_%1.csv")
                              .arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "导出CSV文件",
        defaultName,
        "CSV文件 (*.csv);;所有文件 (*.*)");
    if (filePath.isEmpty())
        return;  // 用户点了取消

    // 3. 打开文件
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        dialog_show("文件打开失败：" + file.errorString());
        return;
    }

    QTextStream out(&file);
    // 4. 写 UTF-8 BOM，解决Excel中文乱码
    out.setEncoding(QStringConverter::Utf8);   // Qt6写法
    // Qt5写法：out.setCodec("UTF-8");
    out << "\xEF\xBB\xBF";

    // 5. 写表头
    out << "采样序号,温度值(℃),采集时间\n";

    // 6. 逐行写数据
    int count = qMin(m_x.size(), m_y.size());
    for (int i = 0; i < count; ++i) {
        QString timeStr = (i < m_times.size())
        ? m_times[i].toString("yyyy-MM-dd HH:mm:ss")
        : "";
        out << QString::number(m_x[i]) << ","
            << QString::number(m_y[i], 'f', 2) << ","
            << timeStr << "\n";
    }

    file.close();
    dialog_show(QString("导出成功！共 %1 条数据\n文件：%2").arg(count).arg(filePath));
}

