#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sstream>
#include <errno.h>
#include "transfer.h"
#include "dbg.h"


const int MAXSIZE = 4096;

int main(int argc, char*argv[])
{

    //创建套接字
    log_info("create socket");
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    check(serv_sock == -1, "create socket error!");
    //配置套接字结构指针 
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("172.20.12.47");
    serv_addr.sin_port = htons(1234);


    //将套接字和IP，端口绑定
    log_info("bind socket");
    int bind_fd = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    check(bind_fd == -1, "bind socket error!");
    
    //进入监听状态,等待客户发出请求
    log_info("listen socketing");
    int listen_fd = listen(serv_sock, 20);
    check(listen_fd == -1, "listen socket error!");
        

    //接受客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock;

    while (1) {

        log_info("accept socket");
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        check(clnt_sock == -1, "accept socket error!");

        //向客户端写入数据
        const char* filename = "tmp.jpg";//如果是多线程，命名需要改变
        //gets(filename);
        FILE* fp = fopen(filename, "wb"); //以二进制方式打开(创建）文件
        check(fp == NULL, "Cannot open file!");

        char buffer[MAXSIZE] = {0};
        int count;
        log_info("file receiving...");
        count = recv(clnt_sock, buffer, 17, 0);
        char magic[] = "xue_seng_xin_yi_";
        check(strcmp(magic, buffer) != 0, "magic error %s", buffer);
        log_info("buffer magic number is %s, count is %d", buffer, count);
        memset(&buffer, 0, sizeof(buffer));
            
        char buffe[30];
        count = recv(clnt_sock, buffe, 20, 0);
        log_info("buffer magic number is %s, count is %d", buffe, count);
        memset(&buffer, 0, sizeof(buffer));
        char buff[30];
        count = recv(clnt_sock, buff, 16, 0);
        log_info("length of the image is %s, count is %d", buff, count);
        memset(&buffer, 0, sizeof(buffer));
        while ((count = recv(clnt_sock, buffer, MAXSIZE, 0))>0) {
            fwrite(buffer, 1, MAXSIZE, fp);
        }
        log_info("file receive successful!");

        fclose(fp);

        //返回文件接受状态给客户端
        //const char* res = "ok";
        //count = write(clnt_sock, res, sizeof(res));
        //if (count == -1) die("lose write\n"); 

        //等待接收动作
        char str[50];
        count = read(clnt_sock, str, sizeof(str)-1);
        check(count == -1, "read false"); 
        log_info("read file:%s", str);
        // 根据命令进行图像处理
        /*
        Improcess* imp = new;
        op;

        */
        // 回传操作后的图像

        FILE* fpn = fopen(filename, "rb"); //以二进制方式打开文件
        check(fpn == NULL, "Cannot open file!");
        
        log_info("file transfering...");
        while ((count = fread(buffer, 1, MAXSIZE, fpn))>0) { 
            send(clnt_sock, buffer, count, 0); 
        }
        //shutdown(clnt_sock, SHUT_RD);

        fclose(fpn);
        //关闭套接字
        close(clnt_sock);
        log_info("file transfer successful!");
    }

    close(serv_sock);

    return 0;
}
