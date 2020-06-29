add_library(common SHARED
transfer.cpp
ImProcess.cc
sock.cc
)

target_link_libraries(common 
    tesseract
    lept
    ${OpenCV_LIBS}
)  
