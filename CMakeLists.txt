cmake_minimum_required(VERSION 3.16)
project(DaSt)

set(CMAKE_CXX_STANDARD 11)

add_executable(DaSt library1.cpp library1.h AVLTree.h Player.cpp Player.h Group.h main.cpp  PlayerManager.h Group.cpp PlayerManager.cpp)
