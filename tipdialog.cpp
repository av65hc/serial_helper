#include "tipdialog.h"
#include "ui_tipdialog.h"

TipDialog::TipDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TipDialog)
{
    ui->setupUi(this);
    ui->label->setWordWrap(true);
    // 限制单行最大宽度，防止窗口拉超长
    ui->label->setMaximumWidth(420);
    // 禁止窗口手动拉伸（可选）
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

TipDialog::~TipDialog()
{
    delete ui;
}
void TipDialog::set_text(QString text){
    ui->label->setText(text);
    // 先让label计算文本尺寸
    ui->label->adjustSize();
    // 对话框自适应整体内容
    this->adjustSize();
    // 可选：窗口不要小于初始最小尺寸
    this->setMinimumSize(240,120);
    adjustSize();
}