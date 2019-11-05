# web server
该项目主要实现了通过客户端向服务器端发送命令以及图片或者视频文件，服务器端进行相应的处理,并返回处理后的结果。
# socket基础知识
socket被翻译为套接字，是计算机之间通信的一种约定，通信则涉及到地址（像叫外卖一样），而IP地址是最常用的，但是计算机并不知道IP地址的具体位置，需要通信时，将IP地址封装到到数据包，交给路由器，通过高效的路由算法可以找到IP对应的机器。然后找到对应的端口号进行通信。计算机会为每个网络程序分配独一无二的端口号，端口是虚拟的逻辑上的概念。

## 数据传输方式
- SOCK_STREAM 面向连接，常见的http协议就是该类型
- SOCK_DGRAM 无连接，只传输，无校验，效率较高，典型有视频聊天、语音聊天

## 常用socket函数的接口，
**创建套接字**,头文件为<sys/socket.h> 

    int socket(int af, int type, int protocol); 

- af 是协议簇（Address Family),也就是IP地址类型，常用有AF_INET 表示ipv4 和AF_INET6 表示ipv6
- type 为数据传输协议，有SOCK_STREAM 和SOCK_DGRAM
- protocol 表示传输协议, 有IPPROTO_TCP 和IPPROTO_UDP，可以默认写０

**绑定套接字**,服务器要用bind() 函数把套接字与特定IP和端口绑定起来，客户端用connect()

    int bind(int sock, struct sockaddr* addr, socklen_t addrlen);
    int connect(int sock, struct sockaddr* addr, socklen_t addrlen);

- sock 为socket 文件描述符addr 为sockaddr 结构体变量指针，addrlen 为结构体指针变量大小,可由sizeof() 计算

**监听函数**, 对于服务器端使用bind() 绑定后，需要使用listen() 函数让套接字进入被动监听状态，再调用accept() 函数就可以随时相应客户端的请求了 

    int listen(int sock, int backlog);
    int accept(int sock, struct sockaddr* addr, socklen_t* addrlen);

- sock 为进入监听的套接字，backlog 为请求队列的最大长度 
- accept() 返回一个新的套接字和客户端通信，addr 保存了客户端的IP 地址和端口号
- listen 只是让套接字进入监听状态，accept() 会阻塞后面程序执行，直到来新的请求

**数据的接收和发送**, 使用write() 可以向套接字写入数据，read() 可以从套接字读取数据

    ssize_t write(int fd, const void* buf, size_t nbytes); //失败返回-1，成功返回０
    ssize_t read(int fd, void* buf, size_t nbytes); //失败返回-1，成功返回字节数
    int send(int fd, const char* buf, int len, int flags);
    int recv(int fd, char* buf, int len, int flags);
- fd 为要写入的文件描述符，buf 为要写入的缓冲区地址，nbytes 为要写入的数据字节数
