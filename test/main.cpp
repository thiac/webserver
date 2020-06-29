#include "ImProcess.h"

int main(int argc, char* argv[])
{
    ImProc IP;
    IP.ImgPre(argv[1]);
    IP.Img2Txt(argv[1]);
    return 0;
}

