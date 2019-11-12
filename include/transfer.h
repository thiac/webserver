#ifndef _TRANSFER_H
#define _TRANSFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sstream>
#include "dbg.h"

const int MAXSIZE = 4096;
const int CMDSIZE = 4;
const int MAGICSIZE = 17;
class transfer {
    public:
        transfer();
        void send_file(char* filename, int sock);
        void recv_file(char* filename, int sock);
        ~transfer();
    private:
        void help(void);
        int count = 0;
};

#endif
