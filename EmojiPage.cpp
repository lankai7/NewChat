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

void EmojiPage::on_btn_1_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_1->text());
    this->hide();
}

void EmojiPage::on_btn_2_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_2->text());
    this->hide();
}
void EmojiPage::on_btn_3_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_3->text());
    this->hide();
}
void EmojiPage::on_btn_4_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_4->text());
    this->hide();
}
void EmojiPage::on_btn_5_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_5->text());
    this->hide();
}
void EmojiPage::on_btn_6_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_6->text());
    this->hide();
}
void EmojiPage::on_btn_7_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_7->text());
    this->hide();
}
void EmojiPage::on_btn_8_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_8->text());
    this->hide();
}
void EmojiPage::on_btn_9_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_9->text());
    this->hide();
}
void EmojiPage::on_btn_10_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_10->text());
    this->hide();
}
void EmojiPage::on_btn_11_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_11->text());
    this->hide();
}
void EmojiPage::on_btn_12_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_12->text());
    this->hide();
}
void EmojiPage::on_btn_13_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_13->text());
    this->hide();
}
void EmojiPage::on_btn_14_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_14->text());
    this->hide();
}
void EmojiPage::on_btn_15_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_15->text());
    this->hide();
}
void EmojiPage::on_btn_16_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_16->text());
    this->hide();
}
void EmojiPage::on_btn_17_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_17->text());
    this->hide();
}
void EmojiPage::on_btn_18_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_18->text());
    this->hide();
}
void EmojiPage::on_btn_19_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_19->text());
    this->hide();
}
void EmojiPage::on_btn_20_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_20->text());
    this->hide();
}
void EmojiPage::on_btn_21_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_21->text());
    this->hide();
}

void EmojiPage::on_btn_22_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_22->text());
    this->hide();
}
void EmojiPage::on_btn_23_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_23->text());
    this->hide();
}
void EmojiPage::on_btn_24_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_24->text());
    this->hide();
}
void EmojiPage::on_btn_25_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_25->text());
    this->hide();
}
void EmojiPage::on_btn_26_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_26->text());
    this->hide();
}
void EmojiPage::on_btn_27_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_27->text());
    this->hide();
}
void EmojiPage::on_btn_28_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_28->text());
    this->hide();
}
void EmojiPage::on_btn_29_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_29->text());
    this->hide();
}
void EmojiPage::on_btn_30_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_30->text());
    this->hide();
}
void EmojiPage::on_btn_31_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_31->text());
    this->hide();
}

void EmojiPage::on_btn_32_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_32->text());
    this->hide();
}
void EmojiPage::on_btn_33_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_33->text());
    this->hide();
}
void EmojiPage::on_btn_34_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_34->text());
    this->hide();
}
void EmojiPage::on_btn_35_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_35->text());
    this->hide();
}
void EmojiPage::on_btn_36_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_36->text());
    this->hide();
}
void EmojiPage::on_btn_37_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_37->text());
    this->hide();
}
void EmojiPage::on_btn_38_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_38->text());
    this->hide();
}
void EmojiPage::on_btn_39_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_39->text());
    this->hide();
}
void EmojiPage::on_btn_40_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_40->text());
    this->hide();
}
void EmojiPage::on_btn_41_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_41->text());
    this->hide();
}

void EmojiPage::on_btn_42_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_42->text());
    this->hide();
}
void EmojiPage::on_btn_43_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_43->text());
    this->hide();
}
void EmojiPage::on_btn_44_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_44->text());
    this->hide();
}
void EmojiPage::on_btn_45_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_45->text());
    this->hide();
}
void EmojiPage::on_btn_46_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_46->text());
    this->hide();
}
void EmojiPage::on_btn_47_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_47->text());
    this->hide();
}
void EmojiPage::on_btn_48_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_48->text());
    this->hide();
}
void EmojiPage::on_btn_49_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_49->text());
    this->hide();
}
void EmojiPage::on_btn_50_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_50->text());
    this->hide();
}
void EmojiPage::on_btn_51_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_51->text());
    this->hide();
}

void EmojiPage::on_btn_52_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_52->text());
    this->hide();
}
void EmojiPage::on_btn_53_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_53->text());
    this->hide();
}
void EmojiPage::on_btn_54_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_54->text());
    this->hide();
}
void EmojiPage::on_btn_55_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_55->text());
    this->hide();
}
void EmojiPage::on_btn_56_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_56->text());
    this->hide();
}
void EmojiPage::on_btn_57_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_57->text());
    this->hide();
}
void EmojiPage::on_btn_58_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_58->text());
    this->hide();
}
void EmojiPage::on_btn_59_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_59->text());
    this->hide();
}
void EmojiPage::on_btn_60_clicked()
{

    PlainTextEdit->insertPlainText(ui->btn_60->text());
    this->hide();
}
