#ifndef __CLIENT_H__
#define __CLIENT_H__

#include<iostream>
#include<thread>
#include<QString>
#include<thread>
#include "tcpsocket.h"


using namespace std;


void child_fun(SOCKET fd) {
    int ret;
    char recvBuf[1024];

    while (1) {
        memset(recvBuf, 0, sizeof(recvBuf));
        ret = recv(fd, recvBuf, sizeof(recvBuf), 0);
        if (ret <= 0) {
            err("recv");
            break;
        }
        else{
            cout << recvBuf << endl;
        }
    }
    closesocket(fd);
}

class Client {
public:
    void Client_init(QString Name) {
        init_Socket();
        char recvBuf[1024];
        fd = create_clientSocket("127.0.0.1");
        const char *Buf = new char[1024];
        Buf = Name.toUtf8().constData();
        strncpy(recvBuf, Buf,sizeof(recvBuf));
        recvBuf[sizeof(recvBuf) - 1] = '\0';
        int ret = send(fd, recvBuf, strlen(recvBuf), 0);
        if (ret <= 0) {
            err("send");
            closesocket(fd);
        }

        thread proc_client(child_fun, fd);
        proc_client.detach();

    }
    ~Client() {
        closesocket(fd);
        close_Socket();
    }

    void client_sent(QString buf){
        const char* Buf = new char[1024];
        Buf = buf.toUtf8().constData();
        char recvBuf[1024];
        strncpy(recvBuf, Buf,sizeof(recvBuf));
        recvBuf[sizeof(recvBuf) - 1] = '\0';
        int ret = send(fd, recvBuf, strlen(recvBuf), 0);
        if (ret <= 0) {
            err("send");
        }
    }

private:
    SOCKET fd;

};


#endif
