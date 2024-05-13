cmake_minimum_required(VERSION 3.27)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab4 main.cpp
        BinaryHeap.h
        BinaryTree.h
        Common.h
        Icollection.h
        Ienumerator.h
        Menu.h
        Set.h
        Tree.h)
add_subdirectory(Google_tests)