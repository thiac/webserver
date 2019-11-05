# web server
- 该项目主要实现了通过客户端向服务器端发送命令以及图片或者视频文件，服务器端进行相应的处理,并返回处理后的结果。
# socket基础知识
socket被翻译为套接字，是计算机之间通信的一种约定，通信则涉及到地址（像叫外卖一样），而IP地址是最常用的，但是计算机并不知道IP地址的具体位置，需要通信时，将IP地址封装到到数据包，交给路由器，通过高效的路由算法可以找到IP对应的机器。然后找到对应的端口号进行通信。计算机会为每个网络程序分配独一无二的端口号，端口是虚拟的逻辑上的概念。

## 数据传输方式
- SOCK_STREAM 面向连接，常见的http协议就是该类型
- SOCK_DGRAM 无连接，只传输，无校验，效率较高，典型有视频聊天、语音聊天

## 常用socket函数的接口，
创建套接字,头文件<sys/socket.h>
int socket(int af, int type, int protocol);
- af是协议簇（Address Family),也就是IP地址类型，常用有AF_INET(ipv4)和AF_INET6(ipv6)
- type 为数据传输协议，有SOCK_STREAM和SOCK_DGRAM
- protocol 表示传输协议, 有IPPROTO_TCP和IPPROTO_UDP，可以默认写０
