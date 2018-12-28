cmake_minimum_required(VERSION 3.9)
project(Optional)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)



add_executable(Optional
        #main.cpp
        optional.cpp optional.h
        counted.cpp counted.h
        gtest/gtest_main.cc
        gtest/gtest-all.cc
        tests.inl
        )