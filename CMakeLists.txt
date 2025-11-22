cmake_minimum_required(VERSION 3.10)

project(ASD3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ASD3
    main.cpp
    bintree.cpp
    redblacktree.cpp
)