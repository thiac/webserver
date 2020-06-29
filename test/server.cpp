#include <signal.h>
#include "transfer.h"
#include "sock.h"
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/sendfile.h>

void handler(int sig) {
    
    exit(EXIT_SUCCESS);
}

int set_nonblocking(int sock_fd) {
    if (fcntl(sock_fd, F_SETFL, fcntl(sock_fd, F_GETFL, 0)|O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}

char* temp_name(int i);

int main(int argc, char*argv[])
{

    int serv_sock, clnt_sock, bind_fd, set_opt, listen_fd, sock_fd, epfd, nfds;
    Transfer trans;
    Sock s;
    // 声明epoll_event结构体变量，ev用于注册事件，数组用于回传要处理的事件
    struct epoll_event ev; 
    struct epoll_event events[20];
    // 创建epoll句柄，size为内核监听最大数目
    epfd = epoll_create(256);//生成用于处理accept的epoll专用文件描述符

    s.create_socket(serv_sock);
    set_nonblocking(serv_sock);
    s.bind_socket(bind_fd, serv_sock);
    s.set_socket(set_opt, serv_sock);
    s.listen_socket(listen_fd, serv_sock);

    // 设置与要处理事件相关的文件描述符
    ev.data.fd = serv_sock;

    // 设置要处理的事件类型
    ev.events = EPOLLIN | EPOLLET;

    // 注册epoll事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &ev);

    
    for ( ; ; ) {
        // 等待epoll事件的发生
        // 返回需要处理的事件数目nfds, 如果返回0表示已超时。
        nfds = epoll_wait(epfd, events, 20, 500);
        if (nfds == -1) {
            perror("epoll_wait");
            break;
        }

        // 处理所有发生的事件
        for (int i = 0; i < nfds; i++) {
            // 如果检测到一个新的SOCKET用户连接到了绑定的socket端口，建立新的连接
            if (events[i].data.fd == serv_sock) {
                 s.accept_socket(clnt_sock, serv_sock);

                 set_nonblocking(clnt_sock);
                 
                 // 设置用于读操作的文件描述符
                 ev.data.fd = clnt_sock;

                 // 设置用于注册的读操作事件
                 ev.events = EPOLLIN | EPOLLET;

                 // 注册ev
                 epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &ev);
            }
            // 如果是已连接用户，并且收到数据，那么读入
            else if (events[i].events & EPOLLIN) {
                if ( (sock_fd = events[i].data.fd) < 0)
                    continue;

                //char* filename = "tmp.jpg";
                //char* filename = temp_name(sock_fd);
                //printf("before recv file: %s, from %d\n", filename, sock_fd);
                //trans.recv_file(filename, sock_fd);
                //delete[] filename;
                //printf("recv file finshed\n");
                // 设置用于写操作的文件描述符
                char request[1024];
                recv(sock_fd, request, 1024, 0);
                request[strlen(request)+1] = '\0';
                printf("successeful\n");
                ev.data.fd = sock_fd;

                // 设置用于写操作的注册事件
                ev.events = EPOLLOUT | EPOLLET;
                
                // 修改sockfd上要处理的事件EPOLLIN
                epoll_ctl(epfd, EPOLL_CTL_MOD, sock_fd, &ev);
                if (ev.events & EPOLLIN)
                printf("1\n");
                else if (ev.events & EPOLLOUT)
                printf("2\n");

            }
            // 如果有数据发送
            else if (events[i].events & EPOLLOUT) {
                sock_fd = events[i].data.fd;

                // 回传操作后的图像
                //char* filename = "tmp.jpg";
                //char* filename = temp_name(sock_fd);
                //trans.send_file(filename, sock_fd);
                //delete[] filename;
                char buf[520] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";
                int s = send(sock_fd, buf, strlen(buf), 0);
                int fd = open("1.jpg", O_RDONLY);
                printf("Begin to send\n");
                sendfile(sock_fd, fd, NULL, 250000);
                printf("after to send\n");
                // 设置用于读操作的文件描述符
                //ev.data.fd = sock_fd;

                // 设置用于读操作的注册事件
                //ev.events = EPOLLIN | EPOLLET;

                // 修改sockfd上要处理的事件EPOLLIN
                //epoll_ctl(epfd, EPOLL_CTL_MOD, sock_fd, &ev);
                epoll_ctl(epfd, EPOLL_CTL_DEL, sock_fd, &ev);
                close(sock_fd);
                break;


           }
        }
           
/*
    pid_t pid;
    int i = 0;
    while (1) {

        s.accept_socket(clnt_sock, serv_sock);

        pid = fork();
        //向客户端写入数据
        if (pid < 0) {
            log_err("fork error");
        } else if (pid == 0) {
            signal(SIGCHLD, handler); 
            close(serv_sock);
            char* filename = temp_name(i);
            //char* filename = "tmp.jpg";//如果是多线程，命名需要改变
            trans.recv_file(filename, clnt_sock);
            // 根据命令进行图像处理

            //Improcess* imp = new;
            //op;


            // 回传操作后的图像
            trans.send_file(filename, clnt_sock);
            exit(EXIT_SUCCESS);
        } else {
            //关闭套接字
            close(clnt_sock);
        }
        i++;
    }

*/
    }
    close(serv_sock);

    return 0;
}


char* temp_name(int i) {
    char* filename = new char[20];
    std::stringstream ss;
    ss<<i;
    char num[20];
    ss>>num;

    strcpy(filename, "tmp");
    strcat(filename, num);
    strcat(filename, ".jpg");
    return filename;
}
