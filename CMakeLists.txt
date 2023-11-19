cmake_minimum_required(VERSION 3.27)
project(SHMem)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} SHARED libSHMem.c)
