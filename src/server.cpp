#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include "dbg.h"


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
    //创建套接字
    /* 
    */
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serv_sock == -1) die("create socket error!");
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);


    //将套接字和IP，端口绑定
    int bind_fd = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (bind_fd == -1) die("bind socket error!");
    //进入监听状态,等待客户发出请求
    int listen_fd = listen(serv_sock, 20);
    if (listen_fd == -1) die("listen socket error!");
        

    //接受客户端请求
    printf("==========Waiting for the signal from another star==========\n");
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    int clnt_sock;
    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1) die("accept socket error!");
        


        //向客户端写入数据
        char filename[MAXSIZE];
        //fgets(filename, MAXSIZE, stdin);
        gets(filename);
        FILE* fp = fopen(filename, "wb"); //以二进制方式打开文件
        if (fp == NULL) die("Cannot open file!");
        char buffer[MAXSIZE] = {0};
        int count;
        while ((count = recv(clnt_sock, buffer, MAXSIZE, 0))>0) {
            fwrite(buffer, 1, MAXSIZE, fp);
        }
        puts("file transfer ssccessful!");

        fclose(fp);

        char str[MAXSIZE];
        read(clnt_sock, str, sizeof(str)-1);

        // 进行图像处理
        /*
        Improcess* imp = new;
        op;

        */
        // 回传操作后的图像

        fp = fopen(filename, "rb"); //以二进制方式打开文件
        if (fp == NULL) die("Cannot open file!");
        //char buffer[MAXSIZE] = {0};
        
        while ((count = fread(buffer, 1, MAXSIZE, fp))>0) { 
            send(clnt_sock, buffer, count, 0); 
        }
        shutdown(clnt_sock, SHUT_RD);
        recv(clnt_sock, buffer, MAXSIZE, 0);

        //char res[100] = "It's OK,now!\n";

        //关闭套接字
        close(clnt_sock);
    }

    close(serv_sock);

    return 0;
}
