#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char*argv[])
{
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0); 

    //想服务器发起请求(特定的IP和端口)
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);

    //连接
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    char buffer[40];
    read(sock, buffer, sizeof(buffer)-1);
    
    printf("Message from another star: %s\n", buffer);

    //关闭套接字
    close(sock);
    return 0;
}

   

