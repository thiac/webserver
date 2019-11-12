#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sstream>
#include "transfer.h"
#include "dbg.h"

const int MAXSIZE = 4096;

void send_file(char* filename, int sock);
void recv_file(char* filename, int sock);
void help(void);

int main(int argc, char*argv[])
{
    printf("Give a picture, some magic will happen!\n");

    while (1) {
        //创建套接字
        log_info("create socket");
        int sock = socket(AF_INET, SOCK_STREAM, 0); 

        //向服务器发起请求(特定的IP和端口)
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;  //使用IPv4地址
        serv_addr.sin_addr.s_addr = inet_addr("172.20.12.47");  //具体的IP地址
        serv_addr.sin_port = htons(1234);

        //连接
        log_info("connect to the server");
        connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        char filename[100] = {0}; //文件名
        //TODO 可以加个进度条
        //TODO 发送文件以及相关操作
        send_file(filename, sock); 
        shutdown(sock, SHUT_WR);
        recv_file(filename, sock);
        //关闭套接字
        shutdown(sock, SHUT_RD);
        //close(sock);
    }
    return 0;
}

void send_file(char* filename, int sock) {
    puts("select a picture");
    scanf("%s", filename);
    puts("Honey, please wait a minute!");
    FILE* fp = fopen(filename, "rb");
    check(fp == NULL, "cannot open file");
    char buffer[MAXSIZE] = {0};
    int count;
    char magic[] = "xue_seng_xin_yi_";
    count = send(sock, magic, sizeof(magic), 0);
    log_info("magic send number is %d", count);
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    printf("%ld\n", size);
    std::stringstream ss;
    ss << size;
    char len[16] = {0};
    ss >> len;
    printf("lenth of image is: %s\n", len);
    count = send(sock, len, sizeof(len), 0);
    log_info("send length count is %d", count);
    while ((count = fread(buffer, 1, MAXSIZE, fp))>0) {
            send(sock, buffer, count, 0);
    }
    help();
    char str[100];
    scanf("%s", str);
    send(sock, str, sizeof(str), 0); 
    log_info("file transfer successful!");
    fclose(fp);



}

void recv_file(char* filename, int sock) {
    puts("inputs a new file name:");
    scanf("%s", filename);
    FILE* fp = fopen(filename, "wb");
    check(fp == NULL, "cannot create a new file");
    int count;
    char buffer[MAXSIZE] = {0};
    while ((count = recv(sock, buffer, MAXSIZE, 0))>0) {
        fwrite(buffer, 1, MAXSIZE, fp);
    }

    fclose(fp);
}


void help(void) {
    printf("what's operation do you want?\n");
    printf("Please input the index number of the op:\n");
    printf("1.make the image more clear!\n");
    printf("2.make the image bigger!\n");
    printf("3.make the image smaller!\n");
}
