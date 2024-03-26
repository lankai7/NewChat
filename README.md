<div align="center">

<img src="./res/bak/bak1.png" alt="icon"/>

 <h1 align="center">NewChat(Client)</h1>

 简体中文 / [English](./README_US.md)
	
NewChat客户端----基于Qt框架的tcp/ip聊天室程序

快捷简便的构建自己的私人聊天室，再也不怕聊天信息泄露了

NewChat服务器：https://github.com/lankai7/NewChatServer_windows

[![standard-readme compliant](https://camo.githubusercontent.com/da0e1f4bf0a54a3283639676aa88bfcc5b3ee3377e9246b6de813371e17cf54e/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d57696e646f77732d626c75653f6c6f676f3d77696e646f7773)](https://github.com/lankai7/NewChatServer_windows/tree/master)

[客户端](https://github.com/lankai7/NewChat.git) / [服务端](https://github.com/lankai7/NewChatServer_windows) / [反馈](https://github.com/lankai7/NewChat/issues)

</div>

## NewChat

"NewChat" 是一个基于 C/C++ 框架的 TCP/IP 聊天室客户端，旨在为用户提供实时的文本、图像、语音、聊天功能。它可以与多个客户端建立 TCP 连接，并且允许客户端之间进行即时通讯,利用了Qt进行图形界面设计。

以下是该服务器的一般功能和特点：

1.TCP/IP 连接:

> NewChat 使用 TCP/IP 协议来建立与服务器的连接，确保**稳定的通信和数据传输**。

2.实时聊天功能: 

> 用户可以通过 NewChat **实时**进行文本、图像和语音消息的发送和接收，实现**即时通讯**。

3.多客户端支持: 

> NewChat 允许**多个客户端同时连接**到服务器，从而支持**多用户**同时在线，实现群聊和私聊功能。

4.图形界面设计: 

> 利用 Qt 框架进行图形用户界面（GUI）设计，使用户操作更加**直观友好**，提升用户体验。

5.安全性:

> NewChat 考虑了安全性，在数据传输和用户身份验证方面进行了相应的处理，以**保障用户信息和通信的安全性**。

6.可扩展性:

> NewChat 的设计考虑了可扩展性，可以通过添加**新的功能模块**或者进行性能优化来满足不同场景下的需求。

7.跨平台性:

> 基于 C/C++ 和 Qt 框架开发，NewChat 具有**跨平台**特性，可以在不同操作系统上运行，如Windows、Linux、macOS 等。

8.用户友好性:

> NewChat 设计简洁易用，用户可以通过直观的界面**快速上手**，并享受到**流畅**的聊天体验。

NewChat 为用户提供了一个方便、实时的聊天室平台，使用户能够轻松地与其他用户进行沟通和交流。


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
NewChat/	//项目文件夹
│
├──── res/		//资源文件
│	├── bak/	//背景图
│	├── icons/	//按键图标
│	├── music/	//音频文件
│	└── styles/	//css文件
│
├──── NewChat.pro	//项目文件
│
├──── xx.h	//头文件
│
├──── xx.cpp	//代码
│
├──── xx.ui	//ui文件
│
└──── xx.qrc	//资源二进制文件
```

对于**数据库的更改**，我采用的是SQLServer，在SQLconnect.h中进行了相关操作的声明，具体实现是在SQLconnect.cpp中

其中在SQLconnect.cpp中更改数据库：

```sh
/*------------------数据库记录用户账户密码--------------------*/
SQLconnect::SQLconnect(){
    // 设置ODBC数据源名称
    db.setDatabaseName("这里是表格名称");
    // 设置连接用户名和密码
    db.setUserName("用户名");
    db.setPassword("密码");
    // 打开数据库连接
    if (db.open()) {
        qDebug() << "Connected to SQL Server!";
    }
}
```

对客户端中通讯连接的**IP与端口号的更改**：
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
>创建一个新文件夹，将项目构建的运行文件NewChat.exe文件放入其中(推荐使用Release构建），运行qtenv2.bat,输入以下指令：

```sh
cd C:\xxx\xxx\   这里是新建的文件夹位置
windeployqt NewChat.exe
```
>等待加载完后即打包成功，可以打开NewChat.exe文件尝试是否成功。

## 徽章

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


## 示例

暂无

## 相关仓库

- [NewChatServer_windows](https://github.com/lankai7/NewChatServer_windows) — windows系统下的NewChat服务器。

## 维护者

[@lankai7](https://github.com/lankai7)。

## 如何贡献

非常欢迎你的加入！[提一个 Issue](https://github.com/lankai7/NewChat/issues/new) 或者提交一个 Pull Request。


## 使用许可

[MIT](LICENSE) © Richard Littauer

