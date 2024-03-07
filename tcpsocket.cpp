#include "tcpsocket.h"
#include<iostream>

using namespace std;
unsigned short PORT = 0x9999;

bool init_Socket() {
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
        err("WSAStartup");
        return false;
    }
    return true;
}

bool close_Socket()
{
    if (WSACleanup() != 0) {
        err("WSACleanup");
        return false;
    }
    return true;
}

/*SOCKET create_serverSocket()
{
    //创建一个空的socket
    SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == fd) {
        err("socket");
        return INVALID_SOCKET;
    }
    //~0 对于有符号来说是-1，对于无符号来说是最大值

    //2，给socket绑定本地ip地址和端口号
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htonl(PORT);	//把本地字节序转化为网络字节序大端存储与小端存储
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	//绑定本地任意ip

    if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr))) {
        err("bind");
        return INVALID_SOCKET;
    }

    //2，开始监听
    listen(fd,10);

    return fd;
}
*/
SOCKET create_clientSocket(const char* ip)
{
    //创建一个空的socket
    SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == fd) {
        err("socket");
        return INVALID_SOCKET;
    }
    //~0 对于有符号来说是-1，对于无符号来说是最大值

    //2，给socket绑定服务端ip地址和端口号
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);	//把本地字节序转化为网络字节序大端存储与小端存储
    addr.sin_addr.S_un.S_addr = inet_addr(ip);	//绑定服务器ip
    if (INVALID_SOCKET == connect(fd, (sockaddr*)&addr, sizeof(addr))){
        err("connect");
        return INVALID_SOCKET;
    }

    cout << "connect success." << endl;



    return fd;
}
