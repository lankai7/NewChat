#pragma once
#ifndef _TCPSOCKET_H_
#define  _TCPSOCKET_H_

#include<iostream>
#include <stdbool.h>
#include <Winsock2.h>
#include <stdio.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")	//库文件

/*tcp网络连接*/

using namespace std;

//报错宏定义
#define err(errMsg) printf("[Error] %s failed,code: %d line:%d \n",errMsg,WSAGetLastError(),__LINE__);

//初始化网络库
bool init_Socket();
//关闭网络库
bool close_Socket();

//服务器：创建服务器socket ---服务端使用
/*SOCKET create_serverSocket();*/

//客户端：创建客户端socket
SOCKET create_clientSocket(const char* ip, const int PORT);


#endif
