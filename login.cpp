#include "login.h"
#include <QtWidgets>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPixmap>
#include <QIcon>
#include "chatwin.h"
#include <QRegularExpression>


login::login(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);

    this->initUI(); //界面
    this->allConnect(); //连接函数

    this->setFixedSize(560,390);    //界面大小
    this->setWindowIcon(QIcon(":/res/icons/icon1.png"));    //icon图片

    //style文件
    QFile file("://res/styles/style.css");
    file.open(QFile::ReadOnly);
    if(!file.isOpen()){
        QMessageBox::warning(this,"","样式加载失败，文件不存在");
    }
    this->setStyleSheet(file.readAll());

}

login::~login()
{

}

void login::onDrag(const QPoint &pos) {
    move(pos);
}

void login::initUI()
{
    //最小化按钮
    QPixmap picMin(":/res/icons/min.png");
    picMin.scaled(30,40);
    miniSizeBtn->setIcon(picMin);
    miniSizeBtn->setFixedSize(30,30);
    //设置对象名
    miniSizeBtn->setObjectName("Btn");
    //关闭按钮
    QPixmap picClose(":/res/icons/close.png");
    picClose.scaled(30,150);
    closeBtn->setIcon(picClose);
    closeBtn->setFixedSize(30,30);
    //设置对象名
    closeBtn->setObjectName("Btn");

    //logo显示
    QPixmap pic(":/res/icons/logo2.png");
    pic.scaled(logoLab->size());
    logoLab->setPixmap(pic);
    logoLab->setFixedSize(265,80);
    logoLab->setScaledContents(true);
    logoLab->setObjectName("logoLab");

    //设置验证器
    QRegularExpression regExp("[a-zA-Z0-9]*");
    QValidator* valid = new QRegularExpressionValidator(regExp, this);

    //账号密码
    accountEdit->setValidator(valid);
    accountEdit->setFixedSize(360,40);
    accountEdit->setPlaceholderText("输入用户名");
    accountEdit->setAlignment(Qt::AlignCenter);

    passwordEdit->setValidator(valid);
    passwordEdit->setFixedSize(360,40);
    passwordEdit->setPlaceholderText("输入密码");
    passwordEdit->setAlignment(Qt::AlignCenter);
    passwordEdit->setEchoMode(QLineEdit::Password);
    //记住密码and忘记密码
    forgetBtn->setFixedSize(80,25);
    forgetBtn->setObjectName("fgtBtn");
    rememberCbx->setObjectName("fgtBtn");

    //登录
    QFont font;
    font.setPointSize(14);
    loginBtn->setFont(font);
    loginBtn->setFixedSize(360,40);
    loginBtn->setObjectName("loginBtn");

    //注册
    registerBtn->setFixedSize(80,25);
    registerBtn->setObjectName("smallBtn");

    //logo以及登录界面表格布局
    QGridLayout* mainLayout = new QGridLayout;

    //logo
    mainLayout->addWidget(logoLab,0,0,1,3);

    //账号密码框
    mainLayout->addWidget(accountEdit,1,0,1,3);
    mainLayout->addWidget(passwordEdit,2,0,1,3);
    //同意协议
    mainLayout->addWidget(rememberCbx,3,0,1,1);
    //忘记密码
    mainLayout->addWidget(forgetBtn,3,2,1,1);
    //登录
    mainLayout->addWidget(loginBtn,4,0,1,3);
    //注册
    mainLayout->addWidget(registerBtn,5,0,1,3);

    //布局间距
    mainLayout->setHorizontalSpacing(0);
    mainLayout->setVerticalSpacing(10);
    mainLayout->setContentsMargins(100,0,100,0);
    // 居中对齐
    mainLayout->setAlignment(Qt::AlignHCenter);
    //
    mainLayout->setAlignment(miniSizeBtn,Qt::AlignTop);
    mainLayout->setAlignment(closeBtn,Qt::AlignTop);
    mainLayout->setAlignment(logoLab,Qt::AlignHCenter);
    mainLayout->setAlignment(registerBtn,Qt::AlignHCenter);

    //最小化按钮和关闭按钮布局
    QGridLayout* minLayout = new QGridLayout;
    //最小化按钮
    minLayout->addWidget(miniSizeBtn,0,0,1,1);
    //关闭按钮
    minLayout->addWidget(closeBtn,0,1,1,1);
    //右上对齐
    minLayout->setAlignment(Qt::AlignRight | Qt::AlignTop);
    minLayout->setContentsMargins(0,5,10,0);

    //总布局
    QVBoxLayout* AllLayout = new QVBoxLayout(this);
    AllLayout->addLayout(minLayout,0);
    AllLayout->addLayout(mainLayout,1);
    //布局间距
    AllLayout->setContentsMargins(0,0,0,30);
    setLayout(AllLayout);

}

void login::allConnect(){
    //自由拖动
    connect(this, &login::dragSignal, this, &login::onDrag);
    //最小化按钮
    connect(miniSizeBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    //关闭按钮
    connect(closeBtn, &QPushButton::clicked, qApp, &QCoreApplication::quit);
    //注册按钮
    connect(registerBtn, &QPushButton::clicked, this, [=](){
        RegisterDialog *registerDialog = new RegisterDialog(this);
        registerDialog->setWindowTitle("注册账号");
        registerDialog->exec();  // 使用 exec() 以模态方式显示对话框
    });
    //忘记密码按钮
    connect(forgetBtn, &QPushButton::clicked, this, [=](){
        forgetDialog* forget = new forgetDialog(this);
        forget->setWindowTitle("找回密码");
        forget->exec();  // 使用 exec() 以模态方式显示对话框
    });
    //登录按钮
    connect(loginBtn,&QPushButton::clicked,this,&login::loginbtn_clicked);

}
/*---------------------鼠标拖动窗口-------------------------*/
void login::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (event->pos().y() < height() / 5) {  // 只有上半部分才允许拖动
            isMousePressed = true;
            dragPosition = event->globalPos() - frameGeometry().topLeft();
        }
    }
}

void login::mouseMoveEvent(QMouseEvent *event) {
    if (isMousePressed) {
        if (event->pos().y() < height() / 5) {  // 只有上半部分才允许拖动
            emit dragSignal(event->globalPos() - dragPosition);
        }
    }
}

void login::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isMousePressed = false;
    }
}
/*-----------------------------------------------------*/
//登录槽函数
void login::loginbtn_clicked(){
    //检测是否勾选同意协议
    if(!rememberCbx->isChecked()){
        QMessageBox::warning(this, "警告", "请勾选已同意服务协议！");
        return;
    }
    //连接数据库
    SQLconnect* SQLcon = new SQLconnect;
    QString id = accountEdit->text();
    if(id==nullptr){
        QMessageBox::warning(this, "警告", "用户名不能为空！");
        return;
    }
    if(!SQLcon->select_ID(id)){
        QMessageBox::warning(this, "警告", "用户名不存在！");
        return;
    }
    QString passw = passwordEdit->text();
    QString Passw = SQLcon->selectPassword(id).trimmed();
    if(passw==nullptr){
        QMessageBox::warning(this, "警告", "密码不能为空！");
        return;
    }
    if(passw!=Passw){
        QMessageBox::warning(this, "警告", "密码不正确！");
        return;
    }

    SQLcon->closeSQL();
    this->close();

    chatwin* chatWin = new chatwin(nullptr,id);
    chatWin->show();

}
/*---------------------绘制窗口圆角-------------------------*/
void login::paintEvent(QPaintEvent *event)
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
