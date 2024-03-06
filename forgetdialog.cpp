#include "forgetdialog.h"
#include "ui_forgetdialog.h"
#include "SQLconnect.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>

forgetDialog::forgetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgetDialog)
{
    ui->setupUi(this);
    //设置验证器
    QRegularExpression regExp("[a-zA-Z0-9]*");
    QValidator* valid = new QRegularExpressionValidator(regExp, this);
    ui->name->setValidator(valid);
    ui->save->setValidator(valid);
    ui->newpsw->setValidator(valid);
    ui->repsw->setValidator(valid);

}

forgetDialog::~forgetDialog()
{
    delete ui;
}

void forgetDialog::on_pushButton_2_clicked()
{
    this->close();
}

void forgetDialog::on_pushButton_clicked()
{
    //连接数据库
    SQLconnect* SQLcon = new SQLconnect;
    QString id = ui->name->text();
    if(!SQLcon->select_ID(id)){
        QMessageBox::warning(this, "警告", "此账户未注册！");
        return;
    }
    if(id==nullptr){
        QMessageBox::warning(this, "警告", "用户名不能为空！");
        return;
    }
    QString saveid = ui->save->text();
    QString save = SQLcon->select_saveID(id);
    if(saveid==nullptr){
        QMessageBox::warning(this, "警告", "安全码不能为空！");
        return;
    }
    if(saveid!=save){
        QMessageBox::warning(this, "警告", "安全码错误！");
        qDebug()<<save<<"  "<<saveid;
        return;
    }
    QString passw = ui->newpsw->text();
    if(passw==nullptr){
        QMessageBox::warning(this, "警告", "密码不能为空！");
        return;
    }
    QString repassw = ui->repsw->text();
    if(repassw!=passw){
        QMessageBox::warning(this, "警告", "两次输入密码不相同！");
        return;
    }

    SQLcon->updateData(id,passw);
    QMessageBox::information(this, "提示", "密码修改成功！");
    SQLcon->closeSQL();
    this->close();
}
