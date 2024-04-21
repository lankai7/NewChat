#ifndef EMOJIPAGE_H
#define EMOJIPAGE_H

#include <QWidget>
#include <QPlainTextEdit>

namespace Ui {
class EmojiPage;
}

class EmojiPage : public QWidget
{
    Q_OBJECT

public:
    explicit EmojiPage(QPlainTextEdit *PlainTextEdit, QWidget *parent = nullptr);
    ~EmojiPage();


private slots:
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_10_clicked();
    void on_btn_11_clicked();
    void on_btn_12_clicked();
    void on_btn_13_clicked();
    void on_btn_14_clicked();
    void on_btn_15_clicked();
    void on_btn_16_clicked();
    void on_btn_17_clicked();
    void on_btn_18_clicked();
    void on_btn_19_clicked();
    void on_btn_20_clicked();
    void on_btn_21_clicked();
    void on_btn_22_clicked();
    void on_btn_23_clicked();
    void on_btn_24_clicked();
    void on_btn_25_clicked();
    void on_btn_26_clicked();
    void on_btn_27_clicked();
    void on_btn_28_clicked();
    void on_btn_29_clicked();
    void on_btn_30_clicked();
    void on_btn_31_clicked();
    void on_btn_32_clicked();
    void on_btn_33_clicked();
    void on_btn_34_clicked();
    void on_btn_35_clicked();
    void on_btn_36_clicked();
    void on_btn_37_clicked();
    void on_btn_38_clicked();
    void on_btn_39_clicked();
    void on_btn_40_clicked();
    void on_btn_41_clicked();
    void on_btn_42_clicked();
    void on_btn_43_clicked();
    void on_btn_44_clicked();
    void on_btn_45_clicked();
    void on_btn_46_clicked();
    void on_btn_47_clicked();
    void on_btn_48_clicked();
    void on_btn_49_clicked();
    void on_btn_50_clicked();
    void on_btn_51_clicked();
    void on_btn_52_clicked();
    void on_btn_53_clicked();
    void on_btn_54_clicked();
    void on_btn_55_clicked();
    void on_btn_56_clicked();
    void on_btn_57_clicked();
    void on_btn_58_clicked();
    void on_btn_59_clicked();
    void on_btn_60_clicked();


private:
    Ui::EmojiPage *ui;
    QPlainTextEdit* PlainTextEdit;
};

#endif // EMOJIPAGE_H
