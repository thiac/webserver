#ifndef IMPROCESS_H
#define IMPROCESS_H
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void die(const char* message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR:%s\n", message);
    }
    exit(1);
}

class ImProc {
public:
/*    explicit ImProc(char* outText, char* lang) {}
    ~ImProc();
    void ImgPreProcess();
    void setLang(char* lang);
*/
    void ImgPre(const char* filename);
    void Img2Txt(const char* file);

private:
    char* outText_;
    char* lang_;
};

#endif
