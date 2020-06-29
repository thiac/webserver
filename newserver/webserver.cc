#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>

const char *INADDR = "127.0.0.1";
const int REQUEST_MAX_SIZE = 4096;

void die(const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR:%s\n", message);
    }

    exit(1);
}


void GetTime(char *curtime) {
    curtime = "12:22:22\n";
    /* TODO */
}

void HandleClient(int clientsock, struct sockaddr_in client_addr);

/**
 * 初始化服务器端的Socket连接，等待连接，连接成功后fork新进程处理
 *
 */
void InitServerListen(unsigned int port, unsigned int maxlisten) {
    int serversock, clientsock;
    struct sockaddr_in server_addr, client_addr;
    char curtime[32];
    
    /* Create TCP socket */
    if ((serversock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        die("Failed to create socket!");
    }

    /* Construct the server sockaddr_in structure */
    memset(&server_addr, 0, sizeof(server_addr));   /* clear struct */
    server_addr.sin_family = AF_INET;   /* Internet/IP */ 
    server_addr.sin_addr.s_addr = inet_addr(INADDR); /* Incomming address */
    server_addr.sin_port = htons(port); /* Server port */

    /* Bind the server socket */
    if (bind(serversock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
           die("Failed to bind the server socket!");
    } 
    
    /* Listen on the server socket */
    if (listen(serversock, maxlisten) < 0) {
        die("Failed to listen on the server socket!");
    }

    /* Print the listen message */
    GetTime(curtime);
    fprintf(stdout, "[%s] Start server listen at port [%d] ...\n", curtime, port);
    fprintf(stdout, "[%s] Waiting client connection ...\n", curtime);

    /* Run until cancelled */
    while (1) {
        unsigned int clientlen = sizeof(client_addr);
        memset(&curtime, 0, sizeof(curtime));
        GetTime(curtime);
        /* Waiting for client connection!" */ 
        if (accept(serversock, (struct sockaddr*) &client_addr, &clientlen) < 0) {
            die("Failed to accept client connection!");
        }

        /* Use child process new connection! */
        if (fork() == 0) {
            HandleClient(clientsock, client_addr);
        } else {
            wait(NULL);
        }

        /* Close the clientsock  */
        close(clientsock);
        
    }
}




int main(int argc, char *argv[]) {
    // unsigned int port = 8000;
    // unsigned int maxlen = 20;
    unsigned int port = atoi(argv[1]);
    unsigned int maxlen = atoi(argv[2]);
    
    InitServerListen(port, maxlen);
    return 0;
}

     
/**
 * 获取一个连接，读取连接客户端发送的请求数据，把请求数据叫给请求解析函数进行解析
 *
 */
void HandleClient(int clientsock, struct sockaddr_in client_addr) {
    char buf[REQUEST_MAX_SIZE];
    if (read(clientsock, buf, REQUEST_MAX_SIZE) < 0) {
        SendError(clientsock, 500, "Internal Server Error", "", "Client Request Not Successed!");
        die("request error!");
        ParseRequest(clientsock, client_addr, buf);
    }
    close(clientsock);
    exit(0);
}

    
/**
 * 解析一个请求，解析出GET/HEAD方法，需要请求的文件，协议版本等，构造成结构体提交给处理函数
 *
 */
int ParseRequest(int clientsock, struct sockaddr_in client_addr, char *buf) {
        



