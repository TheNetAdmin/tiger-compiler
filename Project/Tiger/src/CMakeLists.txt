cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        absyntree.cpp
        absyntree.h
        driver.cpp
        driver.h
        location.hh
        parser.cpp
        parser.h
        position.hh
        scanner.cpp
        stack.hh)

add_executable(src ${SOURCE_FILES})