cmake_minimum_required(VERSION 3.22)
project(abstractVM)
include_directories(/usr/local/include)

set(CMAKE_CXX_STANDARD 14)

add_executable(abstractVM
        src/main.cpp
        src/Factory.cpp
        src/Parser.cpp
        src/VirtualMachine.cpp)