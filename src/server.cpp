#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char*argv[])
{
    //创建套接字
    /* 
    */
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);


    //将套接字和IP，端口绑定
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态,等待客户发出请求
    listen(serv_sock, 20);


    //接受客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);


    //向客户端写入数据
    char str[] = "Hello, world!";
    write(clnt_sock, str, sizeof(str));

    //关闭套接字
    close(clnt_sock);
    close(serv_sock);

    return 0;
}


