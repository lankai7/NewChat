#pragma once
#ifndef __FILEOP_H__
#define  __FILEOP_H__
#include "tcpSocket.h"
#include <vector>
#include "PicByte.h"
class fileoperation{
public:
    long g_fileSize;	//保存文件大小
    QByteArray imageData;   //二进制
    QPixmap pixmap; //图
    char* buf;
    //读取文件（读）
    bool readPic(const char* fileName);
    bool readFile(const char* fileName);

    //发文件
    bool sendFile(SOCKET s);

    /*******客户端********/
    //接收文件
    bool recvFile(SOCKET s);

    //保存文件（写）
    bool saveFile(const char* fileName);

    //处理图片
    bool dealPic();
};


#endif
