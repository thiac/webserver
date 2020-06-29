#include <stdio.h>
#include <string.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#define MAXBUFFER 2048
#define MAXLINE 1024

char* Img2Txt(const char* file) {

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
    // printf("OCR output:\n%s", outText);
 
    // Destroy used object and release memory
    api->End();
    // delete [] outText;
    pixDestroy(&image);
    return outText;
}
int main(int argc, char** argv) {
	char body[MAXBUFFER], content[MAXLINE];
    char* res = Img2Txt(argv[1]);


	//设置消息体
	sprintf(body, "<html><title>ocr</title>");
	sprintf(body, "%s<body bgcolor=""green"">\r\n", body);
	sprintf(body, "%s %s\r\n", body, "200");
	sprintf(body, "%s <p>%s: %s", body, "GET", "success");
	sprintf(body, "%s <p>\n%s\r\n", body, res);
	// sprintf(body, "%s The answer of %d + %d = %d\r\n", body, a, b, a + b);
	sprintf(body, "%s<hr><h3>The Tiny Web Server<h3></body>\r\n", body);
 
	//设置请求头
	sprintf(content, "HTTP/1.1 %s\r\n", "GET");
	sprintf(content, "%sContent-type: text/html\r\n", content);
	sprintf(content, "%sContent-length: %d\r\n", content, 
					(int)strlen(body));
	sprintf(content, "%sEncoding:UTF-8\r\n\r\n", content);
	printf("%s", content);
	printf("%s", body);
    // Img2Txt(argv[1]);
	fflush(stdout);
    return 0;
}

