#ifndef WIDGET_H
#define WIDGET_H
#include <QSerialPort>
#include <QTimer>
#include <QVector>

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;
    QString head_char;
    QString last_char;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void show_text();

    void on_timer_send();   // 定时发送（测试用）

    void on_pushButton_clear_clicked();   // 清空接收区与图表

private:
    Ui::Widget *ui;
    QSerialPort *my_serial;
    void dialog_show(QString text);
    QByteArray m_buffer;   // 接收缓冲区，攒够一帧再解析
    quint16 crc_cal(const QByteArray &data);

    QTimer *m_send_timer;      // 定时发送计时器（测试用）
    QVector<double> m_x;       // 绘图 x 轴（采样序号）
    QVector<double> m_y;       // 绘图 y 轴（温度值）
    int m_index = 0;           // 采样计数
    int max_length = 50;       // 图表最多保留点数
};
#endif // WIDGET_H
