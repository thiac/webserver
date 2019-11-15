#include "transfer.h"

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
        char* filename = "tmp.jpg";//如果是多线程，命名需要改变
        transfer trans;
        trans.recv_file(filename, clnt_sock);

        // 根据命令进行图像处理
        /*
        Improcess* imp = new;
        op;
        */

        // 回传操作后的图像
        trans.send_file(filename, clnt_sock);

        //关闭套接字
        close(clnt_sock);
    }

    close(serv_sock);

    return 0;
}
