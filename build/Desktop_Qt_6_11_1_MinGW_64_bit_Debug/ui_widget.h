/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *mainLayout;
    QGroupBox *groupBox_serial;
    QHBoxLayout *serialLayout;
    QLabel *label_serial;
    QLineEdit *serial;
    QLabel *label_baud;
    QComboBox *baudrate;
    QLabel *label_databit;
    QComboBox *databit;
    QLabel *label_parity;
    QComboBox *parity;
    QLabel *label_stopbit;
    QComboBox *stopbit;
    QPushButton *pushButton_2;
    QHBoxLayout *midLayout;
    QGroupBox *groupBox_recv;
    QVBoxLayout *recvLayout;
    QTextEdit *textEdit;
    QHBoxLayout *recvBtnLayout;
    QPushButton *pushButton_clear;
    QSpacerItem *recvSpacer;
    QVBoxLayout *rightLayout;
    QGroupBox *groupBox_send;
    QVBoxLayout *sendLayout;
    QHBoxLayout *frameLayout;
    QLabel *label_head;
    QLineEdit *lineEdit_2;
    QLabel *label_last;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QGroupBox *groupBox_plot;
    QVBoxLayout *plotLayout;
    QCustomPlot *customplot;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(920, 620);
        Widget->setMinimumSize(QSize(820, 560));
        Widget->setStyleSheet(QString::fromUtf8("QWidget#Widget { background-color: #f5f6fa; }\n"
"QGroupBox {\n"
"    font-weight: bold;\n"
"    color: #2c3e50;\n"
"    border: 1px solid #dcdfe6;\n"
"    border-radius: 6px;\n"
"    margin-top: 12px;\n"
"    padding-top: 6px;\n"
"    background-color: #ffffff;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 12px;\n"
"    padding: 0 4px;\n"
"}\n"
"QPushButton {\n"
"    background-color: #409eff;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"    padding: 6px 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover { background-color: #66b1ff; }\n"
"QPushButton:pressed { background-color: #337ecc; }\n"
"QPushButton:disabled { background-color: #c0c4cc; }\n"
"QLabel {\n"
"    color: #2c3e50;\n"
"}\n"
"QLineEdit {\n"
"    border: 1px solid #dcdfe6;\n"
"    border-radius: 4px;\n"
"    padding: 4px 8px;\n"
"    background-color: #ffffff;\n"
"    color: #2c3e50;\n"
"}\n"
"QLineEdit:focus { border-color: #409eff; }\n"
"QComboBox {\n"
"    border: 1px s"
                        "olid #dcdfe6;\n"
"    border-radius: 4px;\n"
"    min-height: 24px;\n"
"    background-color: #ffffff;\n"
"    color: #2c3e50;\n"
"}\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #dcdfe6;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    border: 1px solid #dcdfe6;\n"
"    background-color: #ffffff;\n"
"    color: #2c3e50;\n"
"    selection-background-color: #409eff;\n"
"    selection-color: #ffffff;\n"
"    outline: 0;\n"
"}\n"
"QTextEdit {\n"
"    border: 1px solid #dcdfe6;\n"
"    border-radius: 4px;\n"
"    font-family: Consolas, \"Courier New\", monospace;\n"
"    font-size: 13px;\n"
"    background-color: #ffffff;\n"
"    color: #2c3e50;\n"
"}"));
        mainLayout = new QVBoxLayout(Widget);
        mainLayout->setObjectName("mainLayout");
        groupBox_serial = new QGroupBox(Widget);
        groupBox_serial->setObjectName("groupBox_serial");
        serialLayout = new QHBoxLayout(groupBox_serial);
        serialLayout->setObjectName("serialLayout");
        label_serial = new QLabel(groupBox_serial);
        label_serial->setObjectName("label_serial");

        serialLayout->addWidget(label_serial);

        serial = new QLineEdit(groupBox_serial);
        serial->setObjectName("serial");
        serial->setMaximumSize(QSize(90, 16777215));

        serialLayout->addWidget(serial);

        label_baud = new QLabel(groupBox_serial);
        label_baud->setObjectName("label_baud");

        serialLayout->addWidget(label_baud);

        baudrate = new QComboBox(groupBox_serial);
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->setObjectName("baudrate");

        serialLayout->addWidget(baudrate);

        label_databit = new QLabel(groupBox_serial);
        label_databit->setObjectName("label_databit");

        serialLayout->addWidget(label_databit);

        databit = new QComboBox(groupBox_serial);
        databit->addItem(QString());
        databit->addItem(QString());
        databit->addItem(QString());
        databit->addItem(QString());
        databit->setObjectName("databit");

        serialLayout->addWidget(databit);

        label_parity = new QLabel(groupBox_serial);
        label_parity->setObjectName("label_parity");

        serialLayout->addWidget(label_parity);

        parity = new QComboBox(groupBox_serial);
        parity->addItem(QString());
        parity->addItem(QString());
        parity->addItem(QString());
        parity->setObjectName("parity");

        serialLayout->addWidget(parity);

        label_stopbit = new QLabel(groupBox_serial);
        label_stopbit->setObjectName("label_stopbit");

        serialLayout->addWidget(label_stopbit);

        stopbit = new QComboBox(groupBox_serial);
        stopbit->addItem(QString());
        stopbit->addItem(QString());
        stopbit->addItem(QString());
        stopbit->setObjectName("stopbit");

        serialLayout->addWidget(stopbit);

        pushButton_2 = new QPushButton(groupBox_serial);
        pushButton_2->setObjectName("pushButton_2");

        serialLayout->addWidget(pushButton_2);


        mainLayout->addWidget(groupBox_serial);

        midLayout = new QHBoxLayout();
        midLayout->setObjectName("midLayout");
        groupBox_recv = new QGroupBox(Widget);
        groupBox_recv->setObjectName("groupBox_recv");
        recvLayout = new QVBoxLayout(groupBox_recv);
        recvLayout->setObjectName("recvLayout");
        textEdit = new QTextEdit(groupBox_recv);
        textEdit->setObjectName("textEdit");
        textEdit->setReadOnly(true);

        recvLayout->addWidget(textEdit);

        recvBtnLayout = new QHBoxLayout();
        recvBtnLayout->setObjectName("recvBtnLayout");
        pushButton_clear = new QPushButton(groupBox_recv);
        pushButton_clear->setObjectName("pushButton_clear");

        recvBtnLayout->addWidget(pushButton_clear);

        recvSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        recvBtnLayout->addItem(recvSpacer);


        recvLayout->addLayout(recvBtnLayout);


        midLayout->addWidget(groupBox_recv);

        rightLayout = new QVBoxLayout();
        rightLayout->setObjectName("rightLayout");
        groupBox_send = new QGroupBox(Widget);
        groupBox_send->setObjectName("groupBox_send");
        sendLayout = new QVBoxLayout(groupBox_send);
        sendLayout->setObjectName("sendLayout");
        frameLayout = new QHBoxLayout();
        frameLayout->setObjectName("frameLayout");
        label_head = new QLabel(groupBox_send);
        label_head->setObjectName("label_head");

        frameLayout->addWidget(label_head);

        lineEdit_2 = new QLineEdit(groupBox_send);
        lineEdit_2->setObjectName("lineEdit_2");

        frameLayout->addWidget(lineEdit_2);

        label_last = new QLabel(groupBox_send);
        label_last->setObjectName("label_last");

        frameLayout->addWidget(label_last);

        lineEdit_3 = new QLineEdit(groupBox_send);
        lineEdit_3->setObjectName("lineEdit_3");

        frameLayout->addWidget(lineEdit_3);


        sendLayout->addLayout(frameLayout);

        lineEdit = new QLineEdit(groupBox_send);
        lineEdit->setObjectName("lineEdit");

        sendLayout->addWidget(lineEdit);

        pushButton = new QPushButton(groupBox_send);
        pushButton->setObjectName("pushButton");

        sendLayout->addWidget(pushButton);


        rightLayout->addWidget(groupBox_send);

        groupBox_plot = new QGroupBox(Widget);
        groupBox_plot->setObjectName("groupBox_plot");
        plotLayout = new QVBoxLayout(groupBox_plot);
        plotLayout->setObjectName("plotLayout");
        customplot = new QCustomPlot(groupBox_plot);
        customplot->setObjectName("customplot");

        plotLayout->addWidget(customplot);


        rightLayout->addWidget(groupBox_plot);

        rightLayout->setStretch(0, 1);
        rightLayout->setStretch(1, 2);

        midLayout->addLayout(rightLayout);

        midLayout->setStretch(0, 3);
        midLayout->setStretch(1, 2);

        mainLayout->addLayout(midLayout);


        retranslateUi(Widget);

        baudrate->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\350\260\203\350\257\225\345\212\251\346\211\213", nullptr));
        groupBox_serial->setTitle(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        label_serial->setText(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\345\217\267", nullptr));
        serial->setPlaceholderText(QCoreApplication::translate("Widget", "\345\246\202 COM1", nullptr));
        label_baud->setText(QCoreApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207", nullptr));
        baudrate->setItemText(0, QCoreApplication::translate("Widget", "9600", nullptr));
        baudrate->setItemText(1, QCoreApplication::translate("Widget", "19200", nullptr));
        baudrate->setItemText(2, QCoreApplication::translate("Widget", "38400", nullptr));
        baudrate->setItemText(3, QCoreApplication::translate("Widget", "57600", nullptr));
        baudrate->setItemText(4, QCoreApplication::translate("Widget", "115200", nullptr));

        label_databit->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\344\275\215", nullptr));
        databit->setItemText(0, QCoreApplication::translate("Widget", "8", nullptr));
        databit->setItemText(1, QCoreApplication::translate("Widget", "7", nullptr));
        databit->setItemText(2, QCoreApplication::translate("Widget", "6", nullptr));
        databit->setItemText(3, QCoreApplication::translate("Widget", "5", nullptr));

        label_parity->setText(QCoreApplication::translate("Widget", "\346\240\241\351\252\214\344\275\215", nullptr));
        parity->setItemText(0, QCoreApplication::translate("Widget", "\346\227\240\346\240\241\351\252\214", nullptr));
        parity->setItemText(1, QCoreApplication::translate("Widget", "\345\245\207\346\240\241\351\252\214", nullptr));
        parity->setItemText(2, QCoreApplication::translate("Widget", "\345\201\266\346\240\241\351\252\214", nullptr));

        label_stopbit->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242\344\275\215", nullptr));
        stopbit->setItemText(0, QCoreApplication::translate("Widget", "1", nullptr));
        stopbit->setItemText(1, QCoreApplication::translate("Widget", "1.5", nullptr));
        stopbit->setItemText(2, QCoreApplication::translate("Widget", "2", nullptr));

        pushButton_2->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        groupBox_recv->setTitle(QCoreApplication::translate("Widget", "\346\216\245\346\224\266\345\214\272", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        groupBox_send->setTitle(QCoreApplication::translate("Widget", "\345\217\221\351\200\201\345\214\272", nullptr));
        label_head->setText(QCoreApplication::translate("Widget", "\345\270\247\345\244\264", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("Widget", "\345\246\202 #", nullptr));
        label_last->setText(QCoreApplication::translate("Widget", "\345\270\247\345\260\276", nullptr));
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("Widget", "\345\246\202 ;", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("Widget", "\350\276\223\345\205\245\350\246\201\345\217\221\351\200\201\347\232\204\346\225\260\346\215\256", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        groupBox_plot->setTitle(QCoreApplication::translate("Widget", "\346\233\262\347\272\277\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
