add_library(common SHARED
transfer.cpp
ImProcess.cc
)

target_link_libraries(common 
    tesseract
    lept
)  
