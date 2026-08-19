/********************************************************************************
** Form generated from reading UI file 'tipdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPDIALOG_H
#define UI_TIPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_TipDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *TipDialog)
    {
        if (TipDialog->objectName().isEmpty())
            TipDialog->setObjectName("TipDialog");
        TipDialog->setWindowModality(Qt::WindowModality::ApplicationModal);
        TipDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(TipDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(TipDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 130, 40, 12));

        retranslateUi(TipDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, TipDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, TipDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(TipDialog);
    } // setupUi

    void retranslateUi(QDialog *TipDialog)
    {
        TipDialog->setWindowTitle(QCoreApplication::translate("TipDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("TipDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TipDialog: public Ui_TipDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPDIALOG_H
