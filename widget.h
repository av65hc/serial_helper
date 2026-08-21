#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>
#include <QVector>
#include "qcustomplot.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDateTime>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void show_text();
    void dialog_show(QString text);
    void on_pushButton_clear_clicked();
    void hex_checked(QByteArray &data);
    void send_cir();
    void checkSerialPortAvailability();
    void on_cycle_time_textChanged(const QString &arg1);
    void on_Hex_send_checkStateChanged(const Qt::CheckState &arg1);

    void on_btnExportCsv_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *my_serial;
    QTimer *cir_send;
    QTimer *m_portCheckTimer;

    QByteArray m_buffer;
    QString head_char;
    QString last_char;
    QVector<QDateTime> m_times;
    QVector<double> m_x;
    QVector<double> m_y;
    int m_index = 0;
    const int max_length = 200;
    const int m_maxBufferSize = 4096;
    quint16 crc_cal(const QByteArray &data);
};

#endif
