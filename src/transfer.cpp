#include "transfer.h"

void Transfer::send_file(char* filename, int sock)
{
    //send magic to detect if whether it is a good connection
    char buffer[MAXSIZE] = {0};
    //char magic[] = "xue_seng_xin_yi_";
    //count = send(sock, magic, sizeof(magic), 0);
    //log_info("magic count is %d", count);

    //It is client if filename is null
    if (strlen(filename) == 0) {
        puts("select a picture");
        scanf("%s", filename);
        puts("Honey, please wait a minute!");
        
        char str[CMDSIZE-1] = {0};
        help();
        scanf("%s", str);
        count = send(sock, str, sizeof(str), 0); 
        log_info("send cmd size is %d:", count);
    }

    FILE* fp = fopen(filename, "rb");
    check(fp == NULL, "cannot open file");
    
    while ((count = fread(buffer, 1, sizeof(buffer), fp))>0) {
            send(sock, buffer, sizeof(buffer), 0);
    }
    log_info("file transfer successful!");
    fclose(fp);
}

void Transfer::recv_file(char* filename, int sock)
{
    log_info("file receiving...");
    char buffer[MAXSIZE] = {0};
    char cmdstr[CMDSIZE] = {0};
    //count = recv(sock, buffer, MAGICSIZE, 0);
    //log_info("receive magic size is: %d", count);
    //char magic[] = "xue_seng_xin_yi_";
    //check(strcmp(magic, buffer) != 0, "magic error, trans fail");
    if (strlen(filename) == 0) {
        puts("inputs a new file name:");
        scanf("%s", filename);
    } else {
        count = recv(sock, cmdstr, CMDSIZE, 0);
        log_info("cmd is: %s, cmd size is: %d", cmdstr, count);
    }

    FILE* fp = fopen(filename, "wb");
    check(fp == NULL, "cannot create a new file");
    while ((count = recv(sock, buffer, MAXSIZE, 0))>0) {
        fwrite(buffer, sizeof(char), count, fp);
        fflush(fp);fsync(fileno(fp));
    }
    
    fclose(fp);
}

void Transfer::help(void)
{
    puts("what's operation do you want?");
    puts("please input the index number of the op:");
    puts("make the image more clear===>>> 1");
    puts("make the image bigger===>>> 2");
    puts("make the image smaller===>>> 3");
}
