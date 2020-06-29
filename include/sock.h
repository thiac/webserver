#ifndef SOCK_H
#define SOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sstream>
#include "dbg.h"


class Sock {
public:
    Sock(const int port = 1234, const char* addr = "127.0.0.1"): PORT(port),
        ADDR(addr) {}
    void create_socket(int& serv_sock);
    void bind_socket(int& bind_fd, int serv_sock);
    void connect_socket(int& serv_sock);
    void set_socket(int& set_opt, int sock);
    void listen_socket(int& listen_fd, int serv_sock);
    void accept_socket(int& clnt_sock, int serv_sock);
private:
    const int PORT;
    const char* ADDR;
};
#endif
