#include "transfer.h"

int main(int argc, char*argv[])
{
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
        transfer tran;
        tran.send_file(filename, sock); 
        shutdown(sock, SHUT_WR);
        memset(&filename, '\0', sizeof(filename));
        tran.recv_file(filename, sock);
        //关闭套接字
        shutdown(sock, SHUT_RD);
        //close(sock);
    }
    return 0;
}
