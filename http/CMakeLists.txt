cmake_minimum_required(VERSION 2.8)
project(webserver)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -W")  

include_directories(/usr/local/include)  
link_directories(/usr/local/lib)  
add_executable(ocr_test ocr.cc)  
target_link_libraries(ocr_test 
    tesseract
    lept
)  
