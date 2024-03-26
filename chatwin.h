void on_file_btn_clicked();
#ifndef CHATWIN_H
#define CHATWIN_H

#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QFile>
#include <QPainter>
#include <QMessageBox>
#include <iostream>
#include <thread>
#include <QString>
#include "tcpsocket.h"
#include "mytextedit.h"
#include "chatmessage.h"
#include "netheader.h"
#include <QStringListModel>
#include <QMutex>
#include <QUrl>
#include <QFileDialog>
#include "PicByte.h"
#include "fileOperation.h"

/*聊天主窗口*/

class QListWidgetItem;

namespace Ui {
class chatwin;
}

class chatwin : public QWidget
{
    Q_OBJECT

public:
    explicit chatwin(QWidget *parent = nullptr, QString Name = QString("Admin"));
    ~chatwin();
    //获取名字
    void get_name(QString Name);
    //客户端初始化
    void Client_init(QString Name);
    //发送信息
    void client_sent(const QString ty, const QString buf);
private:
    //接收信息子进程
    void child_fun(SOCKET fd);

    Ui::chatwin *ui;
    //绘制窗口圆角
    void paintEvent(QPaintEvent *event) override;
    //connect函数集合
    void allConnect();
    //服务器状态
    void online();
    void offline();

    //处理消息与时间
    void dealMessage(ChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QString id ,ChatMessage::User_Type type); //用户发送文本
    void dealMessageTime(QString curMsgTime); //处理时间
    void dealPicture(ChatMessage *messageP, QListWidgetItem *item, QPixmap pixmap, QString time, QString id ,ChatMessage::User_Type type);
    void dealSystem(ChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QString id ,ChatMessage::User_Type type);
private:
    //滚动条
    QScrollBar* vScrollbar;
    //鼠标状态
    bool isMousePressed;
    //鼠标位置坐标
    QPoint dragPosition;

    //ip与端口号
    const char* c_ip = "127.0.0.1";
    const int c_PROT = 9999;
    //客户端连接
    SOCKET fd;
    //客户端名称
    QString name_Me;
    //接收消息
    QString str;
    //文件信息传输
    fileoperation* fileMe;
    fileoperation* fileShe;
    QMutex mutex;

    //消息类型
    QString type_msg_ = "type_msg_";    //消息
    QString type_pic_ = "type_pic_";    //图片
    QString type_sys_ = "type_sys_";    //系统

    //初始化
    void initUI();

    QPixmap picRule(QPixmap pixmap);


public slots:
    //收到信息界面更新
    void recvMsg(const QString Name_she, const QString text);
    //发送信息界面更新
    void sendMsg(const QString text);
    //收到信息界面更新
    void recvPic(const QString Name_she, const QPixmap pic);
    //发送图片界面更新
    void sendPic(const QPixmap pic);
    //系统信息界面更新
    void sysMsg(const QString Name_she, const QString text);

private slots:
    //窗口移动
    void onDrag(const QPoint &pos) {
        move(pos);
    }

    //关闭按钮
    void on_close_btn_clicked();
    //最小化按钮
    void on_min_btn_clicked();
    //发送按钮
    void on_enter_btn_clicked();

    //音乐按钮
    void on_mus_btn_clicked();
    //发送文件
    void on_file_btn_clicked();

    void on_pic_btn_clicked();

    void on_cut_btn_clicked();

    void on_zd_btn_clicked();

signals:
    //移动窗口信号
    void dragSignal(const QPoint&);
    //聊天输出
    void PushText(MSG_TYPE, QString = "");
    //收到消息信号
    void resultReady_She(const QString &Name_she, const QString &text);
    //发送消息信号
    void resultReady_Me(const QString &text);
    //收到图片信号
    void Pic_She(const QString &Name_she, const QPixmap pic);
    //发送图片信号
    void Pic_Me(const QPixmap pic);
    //系统信号
    void Sys_Msg(const QString &Name_she, const QString &text);

protected:
    //窗口可以拖动鼠标事件
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;


};

#endif // CHATWIN_H
