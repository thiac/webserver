#ifndef _TRANSFER_H
#define _TRANSFER_H

#include "sock.h"

const int MAXSIZE = 4096;
const int CMDSIZE = 20;
const int MAGICSIZE = 20;
class Transfer {
    public:
        //transfer();
        void send_file(char* filename, int sock);
        void recv_file(char* filename, int sock);
        //~transfer();
    private:
        void help(void);
        int count = 0;
};

#endif
