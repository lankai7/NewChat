<div align="center">

<img src="./res/bak/bak1.png" alt="icon"/>

 <h1 align="center">NewChat(Client)</h1>

 简体中文 / [English](./README_US.md)
	
NewChat服务器----基于Qt框架的tcp/ip聊天室服务器 -windows版本（后续会有linux版）

快捷简便的构建自己的私人服务器，再也不怕聊天信息泄露了

NewChat客户端：https://github.com/lankai7/NewChat

[![standard-readme compliant](https://camo.githubusercontent.com/da0e1f4bf0a54a3283639676aa88bfcc5b3ee3377e9246b6de813371e17cf54e/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d57696e646f77732d626c75653f6c6f676f3d77696e646f7773)](https://github.com/lankai7/NewChatServer_windows/tree/master)

[客户端](https://github.com/lankai7/NewChat) / [服务端](https://github.com/lankai7/NewChatServer_windows) / [反馈](https://github.com/lankai7/NewChatServer_windows/issues)

</div>

## NewChat_Server

"NewChat_Server" 是一个基于 C/C++ 框架的 TCP/IP 聊天室服务器，旨在为用户提供实时的文本、图像、语音、聊天功能。它可以与多个客户端建立 TCP 连接，并且允许客户端之间进行即时通讯,利用了Qt进行图形界面设计。

以下是该服务器的一般功能和特点：

1.采用[TCP/IP 协议](https://baike.baidu.com/item/TCP%2FIP%E5%8D%8F%E8%AE%AE/212915?fr=ge_ala)的连接管理方式。

2.简单便捷的消息传递，支持文字、图片、语音、文件等**多种数据传输**。

3.简便的用户管理，**即时**查看与管理。

4.**统一**的消息格式，便于查看与阅读。

5.Qt平台设计图形界面，分布精美。

6.具有**良好的安全性**，防止消息泄露。

7.拥有**日志记录**与输出，自动**记录在文件**中，便于查询问题。

8.利用**C/C++作为底层逻辑**，具有良好的**跨平台性**。

Chat_Server 服务器为用户提供了一个方便、实时的聊天室平台，使用户能够轻松地与其他用户进行沟通和交流。


## 内容列表

- [背景](#背景)
- [安装](#安装)
- [使用说明](#使用说明)
	- [打包](#打包)
- [徽章](#徽章)
- [示例](#示例)
- [相关仓库](#相关仓库)
- [维护者](#维护者)
- [如何贡献](#如何贡献)
- [使用许可](#使用许可)

## 背景

`NewChat` 最开始因为本人在大学期间学习linux课程学期末时，在**linux系统**下设计了一款聊天室应用，当时在linux系统下初步完成了以**C语言**为核心的[Socket通信](https://baike.baidu.com/item/sockets/3505925?fr=aladdin) 项目雏形。之后步入寒假，由于寒假假期无聊，于是想着在**windows系统**下利用[Qt](https://baike.baidu.com/item/Qt/451743?fr=ge_ala) 进行界面设计，重新设计一下此应用，于是这个项目由此产生。

> 在windows上进行重写时，第一时间先在vs上重新了构造了linux下的核心内容，并且将编译语言从C语言逐步**向C++过渡**，最后设计成以C++为主的核心代码。

> 核心功能实现之后，便想到了利用Qt来进行图形界面设计，虽然Qt有自身的QSocket通讯，但是最后还是保留了**C/C++的方式**，因为QSocket同样是封装的C/C++的方式，为了自己更好地学习，采用底层逻辑更有助于自身的知识积累。

部分功能已经实现完成，主要的功能已经尽数完结，但为了应用更加完备，将会慢慢的继续更新内容。

同时，此应用完全由自己构思设计，在现代技术chat-GPT的帮助下事半功倍。

对于现代通信来说：

1. 基于对当前网络通信和即时通讯应用的需求和趋势的观察和分析，人们对即时通讯工具的需求越来越高。
2. 考虑到网络通信的安全性和稳定性，确保用户的信息和通信内容不会被泄露或者篡改，局域网通信是不错的方法。
3. 现代生活人们生活在网络中，几乎人人都是透明的，一款简单方便的家庭便捷联系方式将会有效的保护人们隐私。
4. NewChat不仅仅局限于局域网，在广域网中同样可用。
5. 自己架设服务器进行连接，构建自己的私人聊天室。

## 安装

这个项目使用 [C++](https://zh.wikipedia.org/zh-cn/C%2B%2B) 和 [Qt](https://doc.qt.io/)。 编译。如果想要构建项目，请使用Qt4~Qt5版本.

```sh
$ Qt-version：5.12.10
$ C++ 11
```

后续会添加客户端与服务器的安装包，不用构建项目，直接下载应用！

## 使用说明

将项目文件完整下载解压后，使用Qt打开项目文件夹下的.pro文件，选择组件构筑项目。

**项目文件构成：**
```sh
Chat_Server/	//项目文件夹
│
├──── icon/		//图标文件
│
├──── res/	
│	│
│	└── pic/	//背景文件
│
├──── Chat_Server.pro	//项目文件
│
├──── xx.h	//头文件
│
├──── xx.cpp	//代码
│
├──── xx.ui	//ui文件
│
└──── xx.qrc	//资源二进制文件
```

对于**日志文件**，在项目构建的目录下会自动生成/log/文件夹，日志文件保存在以输出时的日期作为名字的txt文件中，日志文件中带有输出时的时间。

其中日志文件文件夹创建：

```sh
/*------------------日志文件文件夹创建--------------------*/
//创建日志文件夹
    QString folderName = "logs";
        QDir dir;
        if (!dir.exists(folderName)) {
            if (dir.mkdir(folderName)) {
                qDebug() << "Folder created successfully: " << folderName;
            } else {
                qDebug() << "Failed to create folder: " << folderName;
            }
        } else {
            qDebug() << "Folder already exists: " << folderName;
        }
```

对服务器中通讯连接的**IP与端口号的更改**在widget.h头文件中：
>⚠️ 注意：客户端与服务器的的IP与端口号**必须一致**才可以进行通讯

```sh
    //ip与端口号 
    const char* c_ip = "127.0.0.1";
    const int c_PROT = 9999;
```

报错宏定义格式：

```sh
//报错宏定义
#define err(errMsg) printf("[Error] %s failed,code: %d line:%d \n",errMsg,WSAGetLastError(),__LINE__);
```

### 打包

想要将项目打包成可执行应用的话，请参考 [QT如何打包生成独立可执行.exe文件](https://blog.csdn.net/weixin_44788542/article/details/130604790)。

>有一个Qt命令终端来打包应用所需的环境与资源，可以在Qt文件夹中找到 `qtenv2.bat`。目录位置：

```sh
QT\5.12.10\mingw73_64\bin\qtenv2.bat
```

>创建一个快捷方式，目标添加前缀C:\Windows\System32\cmd.exe：/A /Q /K 

```sh
C:\Windows\System32\cmd.exe /A /Q /K C:\xxxx\QT\5.12.10\mingw73_64\bin\qtenv2.bat
#C:\xxxx\QT\5.12.10\mingw73_64\bin\qtenv2.bat 改成qtenv2.bat的地址
```
>创建一个新文件夹，将项目构建的运行文件Chat_Server.exe文件放入其中(推荐使用Release构建），运行qtenv2.bat,输入以下指令：

```sh
cd C:\xxx\xxx\   这里是新建的文件夹位置
windeployqt Chat_Server.exe
```
>等待加载完后即打包成功，可以打开NewChat.exe文件尝试是否成功。

## 徽章

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


## 示例

暂无

## 相关仓库

- [NewChat](https://github.com/lankai7/NewChat) — NewChat客户端。

## 维护者

[@lankai7](https://github.com/lankai7)。

## 如何贡献

非常欢迎你的加入！[提一个 Issue](https://github.com/RichardLitt/standard-readme/issues/new) 或者提交一个 Pull Request。


## 使用许可

[MIT](LICENSE) © Richard Littauer

