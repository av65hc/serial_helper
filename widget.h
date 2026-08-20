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

    void on_pushButton_clear_clicked();

    void on_Hex_send_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::Widget *ui;
    QSerialPort *my_serial;
    void dialog_show(QString text);
    void hex_checked(QByteArray &data);
    QByteArray m_buffer;
    quint16 crc_cal(const QByteArray &data);

    QVector<double> m_x;
    QVector<double> m_y;
    int m_index = 0;
    int max_length = 50;
};
#endif // WIDGET_H
