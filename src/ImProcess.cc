#include "ImProcess.h"

void ImProc::ImgPre(const char* file) {
    Mat img = imread(file);
    if (img.data == nullptr) die("read image error");

    //转成灰度图
    Mat grey;
    cvtColor(img, grey, COLOR_BGR2GRAY);
    imshow("grey", grey);
    waitKey(1000);
    //二值化
    Mat img_bin;
    adaptiveThreshold(grey, img_bin, 255, ADAPTIVE_THRESH_MEAN_C,
            THRESH_BINARY_INV, 11, 12);
    imwrite(file, img_bin);
}


void ImProc::Img2Txt(const char* file) {

    char *outText;
 
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng+chi_sim")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
 
    // Open input image with leptonica library
    Pix *image = pixRead(file);
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);
 
    // Destroy used object and release memory
    api->End();
    delete [] outText;
    pixDestroy(&image);
}
