#include "EmojiPage.h"
#include "ui_EmojiPage.h"
#include "chatwin.h"

EmojiPage::EmojiPage(QPlainTextEdit *PlainTextEdit, QWidget *parent) :
    QWidget(parent),
    PlainTextEdit(PlainTextEdit),
    ui(new Ui::EmojiPage)
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0, "😀"); // 改变第一个标签页的名称
    ui->tabWidget->setTabText(1, "💖"); // 改变第二个标签页的名称
    ui->tabWidget->setTabText(2, "🫰"); // 改变第二个标签页的名称


}

EmojiPage::~EmojiPage()
{
    delete ui;
}

void EmojiPage::on_pushButton_6_clicked()
{

    PlainTextEdit->insertPlainText(ui->pushButton_6->text());
    this->hide();
}

void EmojiPage::on_pushButton_3_clicked()
{
    this->hide();
}
