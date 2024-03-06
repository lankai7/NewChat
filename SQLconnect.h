#ifndef SQLCONNECT_H
#define SQLCONNECT_H
#pragma once
#endif // SQLCONNECT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/*数据库操作*/

class SQLconnect{
public:
    // 添加SQL Server数据库驱动程序
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    SQLconnect();
    ~SQLconnect();

    // 插入数据
    void insertData(const QString &ID, const QString &password, const QString &saveID);

    // 查询数据
    QString selectPassword(const QString& qID);
    QString select_saveID(const QString& qID);
    bool select_ID(const QString& qID);

    // 更新数据
    void updateData(const QString &qID, const QString &newPassword);
    void closeSQL();
};
