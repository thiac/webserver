#include "transfer.h"

void transfer::send_file(char* file, int sock)
{
    //send magic to detect if whether it is a good connection
    char buffer[MAXSIZE] = {0};
    char magic[] = "xue_seng_xin_yi_";
    count = send(sock, magic, sizeof(magic), 0);
    log_info("magic count is %d", count);

    //we are client if filename is null
    if (filename == NULL) {
        puts("select a picture");
        scanf("%s", filename);
        puts("Honey, please wait a minute!");
        
        char str[CMDSIZE] = {0};
        help();
        scanf("%s", str);
        send(sock, str, sizeof(str), 0); 
    }

    FILE* fp = fopen(filename, "rb");
    check(fp == NULL, "cannot open file");

    //send length of the file
    //fseek(fp, 0, SEEK_END);
    //long size = ftell(fp);
    //rewind(fp);
    //std::stringstream ss;
    //ss << size;
    //char len[16] = {0};
    //ss >> len;
    //printf("lenth of image is: %s\n", len);
    //count = send(sock, len, sizeof(len), 0);
    //log_info("send length count is %d", count);
    
    while ((count = fread(buffer, 1, MAXSIZE, fp))>0) {
            send(sock, buffer, count, 0);
    }
    log_info("file transfer successful!");
    fclose(fp);
}

void transfer::recv_file(char* filename, int sock)
{
    log_info("file receiving...");
    char buffer[MAXSIZE] = {0};
    char cmdstr[CMDSIZE] = {0};
    recv(clnt_sock, buffer, MAGICSIZE, 0);
    char magic[] = "xue_seng_xin_yi_";
    check(strcmp(magic, buffer) != 0, "magic error, trans fail");
    if (filename == NULL) {
        puts("inputs a new file name:");
        scanf("%s", filename);
    } else {
        recv(sock, cmdstr, CMDSIZE, 0);
    }
    FILE* fp = fopen(filename, "wb");
    check(fp == NULL, "cannot create a new file");
    while ((count = recv(sock, buffer, MAXSIZE, 0))>0) {
        fwrite(buffer, 1, MAXSIZE, fp);
    }

    fclose(fp);
}

void transfer::help(void)
{
    puts("what's operation do you want?");
    puts("please input the index number of the op:");
    puts("make the image more clear===>>> 1");
    puts("make the image bigger===>>> 2");
    puts("make the image smaller===>>> 3");
}
