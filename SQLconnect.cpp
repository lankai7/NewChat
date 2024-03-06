#include "SQLconnect.h"

/*------------------数据库记录用户账户密码--------------------*/
SQLconnect::SQLconnect(){
    // 设置ODBC数据源名称
    db.setDatabaseName("NewChatpwd");
    // 设置连接用户名和密码
    db.setUserName("lankai");
    db.setPassword("aini1314");
    // 打开数据库连接
    if (db.open()) {
        qDebug() << "Connected to SQL Server!";
    }
}

SQLconnect::~SQLconnect(){
    QSqlDatabase::removeDatabase("NewChatpwd");
    qDebug() << "Disconnected from database";
}

void SQLconnect::insertData(const QString &ID, const QString &password, const QString &saveID) {
    QSqlQuery query;
    query.prepare("INSERT INTO LPSW (ID, password, saveID) VALUES (?, ?, ?)");
    query.bindValue(0, ID);
    query.bindValue(1, password);
    query.bindValue(2, saveID);

    if (query.exec()) {
        qDebug() << "Data inserted successfully";
    } else {
        qDebug() << "Error: " << query.lastError().text();
    }
}

QString SQLconnect::selectPassword(const QString &qID) { //查密码
    QSqlQuery query;
    query.prepare("SELECT password FROM LPSW WHERE ID = :qID");
    query.bindValue(":qID", qID);

    if (query.exec() && query.next()) {
        QString password = query.value("password").toString();
        return password;
    } else {
        qDebug() << "Error executing query or no matching rows for username:" << qID;
        return QString(); // Return an empty string for now.
    }

}

QString SQLconnect::select_saveID(const QString &qID) {   //查安全码
    QSqlQuery query;
    query.prepare("SELECT saveID FROM LPSW WHERE ID = :qID");
    query.bindValue(":qID", qID);

    if (query.exec() && query.next()) {
        QString saveID = query.value("saveID").toString();
        return saveID;
        qDebug() <<saveID;
    } else {
        qDebug() << "Error executing query or no matching rows for username:" << qID;
        return QString(); // Return an empty string for now.
    }
}

bool SQLconnect::select_ID(const QString &qID){   //查用户名
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM LPSW WHERE ID = :qID");
    query.bindValue(":qID", qID);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    } else {
        qDebug() << "执行查询或检查用户名存在性时出错：" << qID;
        return false;
    }
}

void SQLconnect::updateData(const QString &qID, const QString &newPassword) {
    QSqlQuery query;
    query.prepare("UPDATE LPSW SET password = ? WHERE ID = ?");
    query.bindValue(0, newPassword);
    query.bindValue(1, qID);

    if (query.exec()) {
        qDebug() << "Data updated successfully";
    } else {
        qDebug() << "Error: " << query.lastError().text();
    }
}

void SQLconnect::closeSQL(){
    QSqlDatabase::removeDatabase("NewChatpwd");
    qDebug() << "Disconnected from database";
}
