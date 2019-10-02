cmake_minimum_required(VERSION 3.15)
project(ImageConverter)

set(CMAKE_CXX_STANDARD 14)

# CLiom project setup for MSVC x64

include_directories (${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/../../Libs/x64)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../Libs/x64/raylib.dll
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ImageConverter main.cpp)
target_link_libraries(ImageConverter raylib)