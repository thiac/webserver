cmake_minimum_required(VERSION 2.8)
project(webserver)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -O3 -march=native ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall   -O3 -march=native")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
include_directories(
${PROJECT_SOURCE_DIR}/include
) 


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(common SHARED
transfer.cpp
)

add_executable(client client.cpp)
target_link_libraries(client common)
add_executable(server server.cpp)
target_link_libraries(server common)
