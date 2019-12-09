#include "ImProcess.h"

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
