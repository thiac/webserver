cmake_minimum_required(VERSION 2.8)
project(webserver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -W")  

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(/usr/local/include)  
include_directories(${PROJECT_SOURCE_DIR}/include) 
link_directories(/usr/local/lib)  

add_subdirectory(src)
add_subdirectory(test)


