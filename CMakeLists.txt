cmake_minimum_required(VERSION 3.19)
project(wet1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(wet1
        library1.h
        main1.cpp)
