#include "sock.h"


void Sock::create_socket(int& serv_sock) {
    //创建套接字
    log_info("create socket");
    serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    check(serv_sock == -1, "create socket error!");
}

void Sock::bind_socket(int& bind_fd, int serv_sock) {
    //配置套接字结构指针 
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ADDR);
    serv_addr.sin_port = htons(PORT);

    //将套接字和IP，端口绑定
    log_info("bind socket");
    bind_fd = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    check(bind_fd == -1, "bind socket error!");
}


void Sock::connect_socket(int& sock) {

    //向服务器发起请求(特定的IP和端口)
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(ADDR);  //具体的IP地址
    serv_addr.sin_port = htons(PORT);

    log_info("connect to the server");
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
}
void Sock::set_socket(int& set_opt, int serv_sock) {
    int on = 1;
    set_opt = setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 
    check(set_opt < 0, "setsocketot error");
}

void Sock::listen_socket(int& listen_fd, int serv_sock) {

    //进入监听状态,等待客户发出请求
    log_info("listen socketing");
    listen_fd = listen(serv_sock, 20);
    check(listen_fd == -1, "listen socket error!");
}


void Sock::accept_socket(int& clnt_sock, int serv_sock) {

    //接受客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    log_info("accept socket");
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    check(clnt_sock == -1, "accept socket error!");
}
