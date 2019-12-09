add_executable(client client.cpp)
target_link_libraries(client common)
add_executable(server server.cpp)
target_link_libraries(server common)

add_executable(ocr_cpp_test main.cpp)  
target_link_libraries(ocr_cpp_test 
    common
)  
