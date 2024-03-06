#ifndef FORGETDIALOG_H
#define FORGETDIALOG_H
#pragma once
#include <QDialog>

/*忘记密码窗口*/

namespace Ui {
class forgetDialog;
}

class forgetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit forgetDialog(QWidget *parent = nullptr);
    ~forgetDialog();

private slots:
    //返回按钮
    void on_pushButton_2_clicked();
    //找回密码按钮
    void on_pushButton_clicked();

private:
    Ui::forgetDialog *ui;
};

#endif // FORGETDIALOG_H
