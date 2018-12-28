cmake_minimum_required(VERSION 3.12)
project(exam)

set(CMAKE_CXX_STANDARD 14)

add_executable(exam
        fixed_vector.h
        #doctest.h
        vector_tests.cpp
        #base_vector.h
        )