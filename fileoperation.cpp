#include "fileOperation.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <QDebug>
#include "PicByte.h"
using namespace std;

bool fileoperation::readPic(const char* fileName)
{
    PicByte* picbyte = new PicByte;
    imageData = picbyte->readImageAsByteArray(fileName);
    pixmap = picbyte->createPixmapFromByteArray(imageData);
    buf = imageData.data();
    g_fileSize = imageData.size();
    delete picbyte;
}

bool fileoperation::readFile(const char *fileName)
{

    return true;
}

bool fileoperation::sendFile(SOCKET s)
{
    int ret = send(s, buf, g_fileSize, 0);
    if (ret == SOCKET_ERROR) {
        err("sendFile");
        return false;
    }
    qDebug() << "发送成功：" << g_fileSize << "Byte" << endl;
    return false;
}

bool fileoperation::recvFile(SOCKET s)
{
    buf = new char[g_fileSize];
    int ret = recv(s, buf, g_fileSize, 0);
    if (ret == 0) {
        qDebug() << "服务器正常" << endl;
    }
    else if (ret < 0) {
        err("recv");
    }
    return false;
}

bool fileoperation::saveFile(const char* fileName)
{
    ofstream write;
    write.open("fileName.jpg", ios::binary);
    if (!write) {
        qDebug() << "file open failed: write" << endl;
        return false;
    }

    write.write(buf,g_fileSize);

    write.close();
    return true;
}

bool fileoperation::dealPic()
{
    QByteArray data(buf,g_fileSize);
    PicByte* picbyte = new PicByte;
    pixmap = picbyte->createPixmapFromByteArray(data);
    if(!picbyte->isPicture()){
        qDebug()<<"pixmap is null"<<endl;
    }
    delete picbyte;
}


