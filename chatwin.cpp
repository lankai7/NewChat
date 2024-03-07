#include "chatwin.h"
#include "ui_chatwin.h"
#include <QStyleOption>
#include <QPainterPath>
#include <QKeyEvent>
#include <QObject>
#include <QShortcut>
#include <QScrollBar>
#include <QDesktopServices>
#include <QDebug>
#include <QDateTime>
#include <QStringListModel>
#include <QSound>

chatwin::chatwin(QWidget *parent, QString Name) :
    QWidget(parent),
    ui(new Ui::chatwin),
    name(Name)
{
    //初始化
    this->initUI();
    //全部connect函数
    this->allConnect();
    //style文件
    QFile file("://res/styles/style_chat.css");
    file.open(QFile::ReadOnly);
    if(!file.isOpen()){
        QMessageBox::warning(this,"","样式加载失败，文件不存在");
    }
    //设置style
    this->setStyleSheet(file.readAll());
}

void chatwin::initUI()
{
    ui->setupUi(this);
    this->setWindowTitle("NewChat");
    //窗口初始化
    this->setWindowIcon(QIcon(":/res/icons/icon.png"));
    //透明背景
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);
    //在线状态图片大小缩放
    ui->online->setScaledContents(true);

    //初始化客户端聊天昵称
    class thread proc_client_init(&chatwin::Client_init,this, this->name);
    proc_client_init.detach();

    //最小化图标
    QPixmap picMin(":/res/icons/minblue.png");
    picMin.scaled(30,40);
    ui->min_btn->setIcon(picMin);
    //关闭图标
    QPixmap picClose(":/res/icons/closeblue.png");
    picClose.scaled(30,40);
    ui->close_btn->setIcon(picClose);
    ui->select_line->setPlaceholderText("🔍︎ 搜索");
    // 根据需要隐藏水平滚动条
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 聊天框滚动条对象
    vScrollbar = new QScrollBar(Qt::Vertical, ui->listWidget);
    vScrollbar->setObjectName("vScrollbar");
    // 将垂直滚动条设置到QTableWidget中
    ui->listWidget->setVerticalScrollBar(vScrollbar);

}

chatwin::~chatwin()
{
    delete ui;
    closesocket(fd);
    close_Socket();
}

void chatwin::get_name(QString Name)
{
    this->name=Name;
}
/*----------------客户端初始化-------------------*/
void chatwin::Client_init(QString Name)
{
    init_Socket();
    char recvBuf[1024];
    fd = create_clientSocket("127.0.0.1");
    if(fd == INVALID_SOCKET){
        offline();
    }
    while(fd == INVALID_SOCKET){
        fd = create_clientSocket("127.0.0.1");
    }
    online();
    const char *Buf = new char[1024];
    Buf = Name.toUtf8().constData();
    strncpy(recvBuf, Buf,sizeof(recvBuf));
    recvBuf[sizeof(recvBuf) - 1] = '\0';
    int ret = send(fd, recvBuf, strlen(recvBuf), 0);
    if (ret <= 0) {
        err("send");

        //closesocket(fd);
    }
        class thread proc_client(&chatwin::child_fun,this, fd);
        proc_client.detach();
}
/*---------------客户端发送消息-------------------*/
void chatwin::client_sent(QString buf)
{
    const char* Buf = new char[1024];
    Buf = buf.toUtf8().constData();
    char recvBuf[1024];
    strncpy(recvBuf, Buf,sizeof(recvBuf));
    recvBuf[sizeof(recvBuf) - 1] = '\0';
    int ret = send(fd, recvBuf, strlen(recvBuf), 0);
    if (ret <= 0) {
        err("send");
    }
}

void chatwin::child_fun(SOCKET fd)
{
    int ret;
    char recvBuf[1024];

    while (1) {
        memset(recvBuf, 0, sizeof(recvBuf));
        ret = recv(fd, recvBuf, sizeof(recvBuf), 0);

        if (ret <= 0) {
            err("recv");
//            class thread proc_client_init(&chatwin::Client_init,this, this->name);
//            proc_client_init.detach();
//            break;
            continue;
        }
        else{
            QString strl = QString::fromUtf8(recvBuf);
            qDebug()<<str<<endl;
            emit resultReady_She(strl);
        }
    }
    closesocket(fd);
}

/*------------------绘制窗口圆角-------------------*/
void chatwin::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);    // 反锯齿;
        painter.setBrush(QBrush(Qt::white));
        painter.setPen(Qt::transparent);
        QRect rect = this->rect();
        rect.setWidth(rect.width() - 1);
        rect.setHeight(rect.height() - 1);
        painter.drawRoundedRect(rect, 15, 15);
        //也可用QPainterPath 绘制代替 painter.drawRoundedRect(rect, 15, 15);
        /*{
            QPainterPath painterPath;
            painterPath.addRoundedRect(rect, 15, 15);

        }*/
        QWidget::paintEvent(event);
        QStyleOption opt;
            opt.initFrom(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
            QWidget::paintEvent(event);
            painter.end();


}
/*------------------输入框发送-------------------*/
void chatwin::allConnect()
{
    //自由拖动
    connect(this, &chatwin::dragSignal, this, &chatwin::onDrag);

    // 创建回车键的快捷键，将其连接到按钮的点击槽
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, [this]() {
        QString text = ui->plainTextEdit->toPlainText();
        // 检查是否按下了 Shift 键
        Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
        bool shiftPressed = (modifiers & Qt::ShiftModifier);
        if (text.endsWith('\n')&&!shiftPressed) {
            // 移除最后一个字符（即换行符）
            text.chop(1);
            ui->plainTextEdit->setPlainText(text);
            // 发送
            ui->enter_btn->click();
        }
    });
    //接收与发送消息显示
    connect(this,&chatwin::resultReady_She,this,&chatwin::recvMsg);
    connect(this,&chatwin::resultReady_Me,this,&chatwin::sendMsg);

}
/*---------------服务器在线状态显示----------------*/
void chatwin::online()
{
    //在线状态
    QPixmap pixmap("://res/icons/online.png");
    pixmap.scaled(ui->online->size());
    ui->online->setPixmap(pixmap);
}

void chatwin::offline()
{
    //断线状态
    QPixmap pixmap("://res/icons/offline.png");
    pixmap.scaled(ui->online->size());
    ui->online->setPixmap(pixmap);
}
/*---------------------------------------------------------*/
void chatwin::dealMessage(ChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QString id ,ChatMessage::User_Type type)
{
    ui->listWidget->addItem(item);
    messageW->setFixedWidth(ui->listWidget->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, id, type);
    ui->listWidget->setItemWidget(item, messageW);
}
void chatwin::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        ChatMessage* messageW = (ChatMessage *)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        ChatMessage* messageTime = new ChatMessage(ui->listWidget);
        QListWidgetItem* itemTime = new QListWidgetItem();
        ui->listWidget->addItem(itemTime);
        QSize size = QSize(ui->listWidget->width() , 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void chatwin::sendMsg(QString text)
{
    QString time = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
    ChatMessage *message = new ChatMessage(ui->listWidget);
    QListWidgetItem *item = new QListWidgetItem();
    dealMessageTime(time);
    dealMessage(message, item, text, time, name ,ChatMessage::User_Me);
    ui->listWidget->verticalScrollBar()->setValue(ui->listWidget->verticalScrollBar()->maximum());

}

void chatwin::recvMsg(QString text)
{
    //提示音
    QSound::play("://res/music/msg.wav");
    QString time = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
    ChatMessage *message = new ChatMessage(ui->listWidget);
    QListWidgetItem *item = new QListWidgetItem();
    dealMessageTime(time);
    dealMessage(message, item, text, time, name ,ChatMessage::User_She);
    ui->listWidget->verticalScrollBar()->setValue(ui->listWidget->verticalScrollBar()->maximum());

}

/*--------------------按钮----------------------*/

void chatwin::on_close_btn_clicked()
{
    this->close();
}

void chatwin::on_min_btn_clicked()
{
    this->showMinimized();
}
/*-----------------消息显示界面-------------------*/
void chatwin::on_enter_btn_clicked()
{
    QString msg = ui->plainTextEdit->toPlainText().trimmed();
    if(msg.size() == 0)
    {
        qDebug() << "empty";
        return;
    }
    qDebug()<<msg;
    ui->plainTextEdit->setPlainText("");
    emit resultReady_Me(msg);
    this->client_sent(msg);
}

/*--------------------音乐按钮---------------------*/

void chatwin::on_mus_btn_clicked()
{
    QUrl url("http://goodtdgame.com/"); // 替换为你想要打开的网页地址
    QDesktopServices::openUrl(url);
}

/*-------------------鼠标拖动窗口-------------------*/
void chatwin::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (event->pos().y() < height() / 8) {  // 只有上半部分才允许拖动
            isMousePressed = true;
            dragPosition = event->globalPos() - frameGeometry().topLeft();
        }
    }
}

void chatwin::mouseMoveEvent(QMouseEvent *event) {
    if (isMousePressed) {
        if (event->pos().y() < height() / 8) {  // 只有上半部分才允许拖动
            emit dragSignal(event->globalPos() - dragPosition);
        }
    }
}

void chatwin::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isMousePressed = false;
    }
}
/*--------------------------------------------------*/

