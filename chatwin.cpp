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
#include <algorithm>

chatwin::chatwin(QWidget *parent, QString Name) :
    QWidget(parent),
    ui(new Ui::chatwin),
    name_Me(Name)
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
    std::thread proc_client_init(&chatwin::Client_init,this, this->name_Me);
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
    //消息列表选中取消焦点蓝框

}

QPixmap chatwin::picRule(QPixmap pixmap)
{

    // 获取原始尺寸
    int originalWidth = pixmap.width();
    int originalHeight = pixmap.height();

    // 假设你想要将图片的短边设置为 250 像素，并保持宽高比不变
    int newWidth;
    int newHeight;
    if(originalWidth <= originalHeight){
        newWidth = 250;
        //缩放因子
        float scaleFactor = static_cast<float>(newWidth) / originalWidth;
        //计算高
        newHeight = static_cast<int>(originalHeight * scaleFactor);
    }
    else{
        newHeight = 250;
        float scaleFactor = static_cast<float>(newHeight) / originalHeight;
        newWidth = static_cast<int>(originalWidth * scaleFactor);
    }

    // 缩放图片
    QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return scaledPixmap;

}

chatwin::~chatwin()
{
    delete ui;
    closesocket(fd);
    close_Socket();
}
//获取名字
void chatwin::get_name(QString Name){
    this->name_Me=Name;
}
/*----------------客户端初始化-------------------*/
void chatwin::Client_init(QString Name)
{
    init_Socket();
    fd = create_clientSocket("127.0.0.1");
    while(fd == INVALID_SOCKET){
        offline();
        fd = create_clientSocket("127.0.0.1");
    }
    online();
    // 发送用户名到服务器
    QByteArray utf8Name = Name.toUtf8();
    char sendBuf[1024];
    int copySize = std::min(utf8Name.size(),int(sizeof(sendBuf)));
    // 防止缓冲区溢出
    memcpy(sendBuf, utf8Name.constData(), copySize); // 使用 memcpy 确保不会截断 UTF-8 字符串
    sendBuf[copySize] = '\0'; // 确保字符串正确终止
    qDebug()<<"connect:"<<sendBuf<<endl;
    int ret = send(fd, sendBuf, strlen(sendBuf), 0);
    if (ret <= 0) {
        // 发送失败
        err("send");
        closesocket(fd);
        offline();
        qDebug() << "Failed to send data to server.";
        return;
    }
        // 启动线程处理客户端通信
        std::thread proc_client(&chatwin::child_fun,this, fd);
        proc_client.detach();// 分离线程，允许它在后台运行

}
/*---------------客户端发送消息-------------------*/
void chatwin::client_sent(const QString &buf)
{
    QByteArray byteArray = buf.toUtf8();
    const char *data = byteArray.constData();
    int dataSize = byteArray.size();

    int ret = send(fd, data, dataSize, 0);
    if (ret <= 0) {
        // 假设 err 是一个接受字符串参数的自定义错误处理函数
        err("send data");
    }
}
/*-------------------接收消息--------------------*/
void chatwin::child_fun(SOCKET fd)
{
    int ret;
    char recvName[256];
    char recvBuf[1024];

    while (1) {
        memset(recvName, 0, sizeof(recvName));
        memset(recvBuf, 0, sizeof(recvBuf));
        ret = recv(fd, recvName, sizeof(recvName), 0);
        ret = recv(fd, recvBuf, sizeof(recvBuf), 0);

        if (ret <= 0) {
            err("recv");
            std::thread proc_client_init(&chatwin::Client_init,this, this->name_Me);
            proc_client_init.detach();
            break;
        }
        else{
            name_She = QString::fromUtf8(recvName);
            QString strl = QString::fromUtf8(recvBuf);
            QByteArray byteArray = recvBuf;
            PicByte *picbyte = new PicByte;
            QPixmap pixmap = picbyte->createPixmapFromByteArray(byteArray);
            if(picbyte->isPicture()){
                emit Pic_She(pixmap);
            }
            else{
                qDebug()<<name_She<<":"<<strl<<endl;
                emit resultReady_She(strl);
            }

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
        QStyleOption opt;
        opt.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        QWidget::paintEvent(event);

}
/*------------------输入框发送-------------------*/
void chatwin::allConnect()
{
    //自由拖动
    connect(this, &chatwin::dragSignal, this, &chatwin::onDrag);

    // 创建回车键的快捷键，将其连接到按钮的点击槽
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, [this]() {
        QString text = ui->plainTextEdit->toPlainText();
        QString index = ui->plainTextEdit->toPlainText().replace(" ", "");  // 去除开头和结尾的空白字符
        // 检查是否按下了 Shift 键
        Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
        bool shiftPressed = (modifiers & Qt::ShiftModifier);
        if (index.endsWith('\n')&&!shiftPressed) {
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
    connect(this,&chatwin::Pic_Me,this,&chatwin::sendPic);
    connect(this,&chatwin::Pic_She,this,&chatwin::recvPic);

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
//处理消息显示
void chatwin::dealMessage(ChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QString id ,ChatMessage::User_Type type)
{
    ui->listWidget->addItem(item);
    messageW->setFixedWidth(ui->listWidget->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, id, type);
    ui->listWidget->setItemWidget(item, messageW);

}
//处理时间显示
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
//处理图片显示
void chatwin::dealPicture(ChatMessage *messageP, QListWidgetItem *item, QPixmap pixmap, QString time, QString id ,ChatMessage::User_Type type)
{
    ui->listWidget->addItem(item);
    messageP->setFixedWidth(ui->listWidget->width());
    messageP->fontRect("");
    QSize p_size = pixmap.size();
    item->setSizeHint(p_size);
    messageP->setPicture(pixmap, time, p_size, id, type);
    ui->listWidget->setItemWidget(item, messageP);
}

//接收消息
void chatwin::recvMsg(QString text)
{
    //提示音
    QSound::play("://res/music/msg.wav");
    QString time = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
    ChatMessage *message = new ChatMessage(ui->listWidget);
    QListWidgetItem *item = new QListWidgetItem();
    dealMessageTime(time);
    dealMessage(message, item, text, time, name_She ,ChatMessage::User_She);
    ui->listWidget->verticalScrollBar()->setValue(ui->listWidget->verticalScrollBar()->maximum());

}
//发送消息
void chatwin::sendMsg(QString text)
{
    QString time = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
    ChatMessage *message = new ChatMessage(ui->listWidget);
    QListWidgetItem *item = new QListWidgetItem();
    dealMessageTime(time);
    dealMessage(message, item, text, time, name_Me ,ChatMessage::User_Me);
    ui->listWidget->verticalScrollBar()->setValue(ui->listWidget->verticalScrollBar()->maximum());

}
//接收图片
void chatwin::recvPic(QPixmap pic)
{
    //提示音
    QSound::play("://res/music/msg.wav");
    QPixmap pixmap = picRule(pic);

    QString time = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
    ChatMessage *message = new ChatMessage(ui->listWidget);
    QListWidgetItem *item = new QListWidgetItem();
    dealMessageTime(time);
    dealPicture(message, item, pixmap, time, name_She ,ChatMessage::User_She);
    ui->listWidget->verticalScrollBar()->setValue(ui->listWidget->verticalScrollBar()->maximum());
}
//发送图片
void chatwin::sendPic(QPixmap pic)
{
    QPixmap pixmap = picRule(pic);

    QString time = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
    ChatMessage *message = new ChatMessage(ui->listWidget);
    QListWidgetItem *item = new QListWidgetItem();
    dealMessageTime(time);
    dealPicture(message, item, pixmap, time, name_Me ,ChatMessage::User_Me);
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
    QString msg = ui->plainTextEdit->toPlainText();
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

//聊天功能栏：选择文件
void chatwin::on_file_btn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", ".", "所有文件 (*);;图片 (*.png;*.jpg;*.jpeg;*.gif);;文本 (*.txt;*.doc;*.docx)");
            if (!fileName.isEmpty()) {
                // 如果用户选择了文件，处理文件名或执行其他操作
                QMessageBox::information(this, "选择的文件", "你选择了文件: " + fileName);
            }
}
//发送图片
void chatwin::on_pic_btn_clicked()
{
    PicByte *picbyte = new PicByte;
    QString fileName = QFileDialog::getOpenFileName(this, "选择图片", ".", "图片 (*.png;*.jpg;*.jpeg;*.gif)");
            if (!fileName.isEmpty()) {
                // 如果用户选择了文件，处理文件名或执行其他操作
                //QPixmap pixmap(fileName); // 从文件路径加载图片
                QByteArray imageData = picbyte->readImageAsByteArray(fileName);
                QPixmap pixmap = picbyte->createPixmapFromByteArray(imageData);
                this->client_sent(QString::fromUtf8(imageData));
                qDebug()<<"***"<<QString::fromUtf8(imageData);
                emit Pic_Me(pixmap);
            }

}
