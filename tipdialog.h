#ifndef TIPDIALOG_H
#define TIPDIALOG_H

#include <QDialog>

namespace Ui {
class TipDialog;
}

class TipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TipDialog(QWidget *parent = nullptr);
    ~TipDialog();
    void set_text(QString text);

private:
    Ui::TipDialog *ui;
};

#endif // TIPDIALOG_H
