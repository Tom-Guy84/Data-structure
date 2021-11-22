cmake_minimum_required(VERSION 3.16)
project(DaSt)

set(CMAKE_CXX_STANDARD 11)

add_executable(DaSt library1.h AVLTree.h Player.cpp Player.h main.cpp Group.h PlayerManager.h Group.cpp)
