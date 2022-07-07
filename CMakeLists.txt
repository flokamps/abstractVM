cmake_minimum_required(VERSION 3.22)
project(abstractVM)

set(CMAKE_CXX_STANDARD 14)

add_executable(abstractVM
        src/main.cpp
        src/Type.cpp
        src/Factory.cpp)