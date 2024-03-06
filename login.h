#ifndef LOGIN_H
#define LOGIN_H
#pragma once
#include <QWidget>
#include <QMouseEvent>
#include "registerdialog.h"
#include "forgetdialog.h"
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QFile>
#include <QMessageBox>
#include <QCoreApplication>
#include "SQLconnect.h"
#include <QPainter>
#include <QBitmap>

/*登录主界面*/

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    //最小化按钮
    QPushButton* miniSizeBtn = new QPushButton;
    //关闭按钮
    QPushButton* closeBtn = new QPushButton;
    //logo显示
    QLabel* logoLab = new QLabel;
    //账号密码
    QLineEdit* accountEdit = new QLineEdit;
    QLineEdit* passwordEdit = new QLineEdit;
    //记住密码
    QCheckBox* rememberCbx = new QCheckBox("已阅读并同意服务协议");
    //忘记密码
    QPushButton* forgetBtn = new QPushButton("忘记密码");
    //登录
    QPushButton* loginBtn = new QPushButton("登录");
    //注册
    QPushButton* registerBtn = new QPushButton("注册账号");


private slots:
    //鼠标拖动
    void onDrag(const QPoint &pos);
    //登录按钮
    void loginbtn_clicked();
    //窗口绘制圆角
    void paintEvent(QPaintEvent *event) override;

signals:
    void dragSignal(const QPoint&);


private:
    Ui::login *ui;
    void initUI();//登录ui界面
    void allConnect();//连接信号与槽
    //鼠标状态
    bool isMousePressed;
    //鼠标位置
    QPoint dragPosition;

protected:
        //鼠标可以拖动窗口
        void mousePressEvent(QMouseEvent *event) override;

        void mouseMoveEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // LOGIN_H
