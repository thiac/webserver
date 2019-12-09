#ifndef IMPROCESS_H
#define IMPROCESS_H
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class ImProc {
public:
/*    explicit ImProc(char* outText, char* lang) {}
    ~ImProc();
    void ImgPreProcess();
    void setLang(char* lang);
*/
    void Img2Txt(const char* file);

private:
    char* outText_;
    char* lang_;
};

#endif
