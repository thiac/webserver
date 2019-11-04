#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include "dbg.h"

const int BUFSIZE = 4096;
const int MAXSIZE = 4096;

void die(const char* message)
{
    if (errno)
        perror(message);
    else
        printf("ERROR: %s\n", message);
    exit(1);
} 

int main(int argc, char*argv[])
{
    printf("\tGive a picture, some magic will happen!\n");

    while (1) {
        //创建套接字
        int sock = socket(AF_INET, SOCK_STREAM, 0); 

        //向服务器发起请求(特定的IP和端口)
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;  //使用IPv4地址
        serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
        serv_addr.sin_port = htons(1234);

        //连接
        connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        
        printf("Please select a picture, tell me where is it?\n");

        //TODO 对图像进行转换，并发送给服务器端
        // 选择一种操作，留给服务器进行处理
        char filename[100] = {0}; //文件名
        gets(filename);
        //fgets(filename, sizeof(filename), stdin);
        //fflush(stdin);
        FILE* fp = fopen(filename, "rb"); //以二进制方式打开文件
        if (fp == NULL) die("Cannot open file!");
        char buffer[BUFSIZE] = {0}; //缓冲区
        int count;
        //发送文件
        //TODO 以及相关操作

        while ((count = fread(buffer, 1, BUFSIZE, fp))>0) { 
            send(sock, buffer, count, 0); 
        }

        printf("what's operation do you want?\n");
        printf("Please input the index number of the op:\n");
        printf("1.make the image more clear!\n");
        printf("2.make the image bigger!\n");
        printf("3.make the image smaller!\n");

        char str[MAXSIZE];
        fgets(str, MAXSIZE, stdin);
        write(sock, str, sizeof(str)); 

        //接受处理后的文件
        /*while ((count = recv(sock, buffer, BUFSIZE, 0))>0) {
            fwrite(buffer, 1, BUFFSIZE, fp);
        }*/
        // 断开链接
        
        



        /*char str[MAXSIZE];
        char buffer[MAXSIZE];
        fgets(str, MAXSIZE, stdin);
        read(sock, buffer, sizeof(buffer)-1);
        printf("elien:%s", buffer); */

        fclose(fp);
        //关闭套接字
        close(sock);
        printf("If you like, you can go on.....\n");
    }
    return 0;
}

   

