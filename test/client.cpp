#include "transfer.h"
#include "sock.h"

int main(int argc, char*argv[])
{
    while (1) {
        //创建套接字
        int sock;
        Sock s;
        s.create_socket(sock);

        //连接
        s.connect_socket(sock);
        char filename[100] = {0}; //文件名
        //TODO 可以加个进度条
        //TODO 发送文件以及相关操作
        Transfer tran;
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
