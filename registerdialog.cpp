#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "SQLconnect.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //设置验证器
    QRegularExpression regExp("[a-zA-Z0-9]*");
    QValidator* valid = new QRegularExpressionValidator(regExp, this);
    ui->name->setValidator(valid);
    ui->save->setValidator(valid);
    ui->psword1->setValidator(valid);
    ui->psword2->setValidator(valid);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_pushButton_2_clicked()
{
    this->close();
}
//注册按钮
void RegisterDialog::on_pushButton_clicked()
{
    //连接数据库
    SQLconnect* SQLcon = new SQLconnect;
    QString id = ui->name->text();
    if(SQLcon->select_ID(id)){
        QMessageBox::warning(this, "警告", "用户名已被使用！");
        return;
    }
    if(id==nullptr){
        QMessageBox::warning(this, "警告", "用户名不能为空！");
        return;
    }
    QString passw = ui->psword1->text();
    if(passw==nullptr){
        QMessageBox::warning(this, "警告", "密码不能为空！");
        return;
    }
    QString repassw = ui->psword2->text();
    if(repassw!=passw){
        QMessageBox::warning(this, "警告", "两次输入密码不相同！");
        return;
    }
    QString saveid = ui->save->text();
    if(saveid==nullptr){
        QMessageBox::warning(this, "警告", "安全码不能为空！");
        return;
    }
    if(saveid.size()!=6){
        QMessageBox::warning(this, "警告", "请输入6位安全码！");
        return;
    }

    SQLcon->insertData(id,passw,saveid);
    QMessageBox::information(this, "提示", "注册成功！");
    SQLcon->closeSQL();
    this->close();
}
