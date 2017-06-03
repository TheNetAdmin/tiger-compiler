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
        stack.hh Semantic.h Semantic.cpp Semantic.h Types.cpp Types.h Translate.cpp Translate.h Env.cpp Env.h Error.cpp Error.h
        Debug.cpp Debug.h
        BoolList.h Frame.cpp Frame.h IR.cpp IR.h Translate.cpp Translate.h Temporary.cpp Temporary.h
        ../test/sem_test.cpp
        PrintIRTree.cpp PrintIRTree.h)

add_executable(src ${SOURCE_FILES})