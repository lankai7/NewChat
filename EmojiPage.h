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
    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::EmojiPage *ui;
    QPlainTextEdit* PlainTextEdit;
};

#endif // EMOJIPAGE_H
