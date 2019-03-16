cmake_minimum_required(VERSION 3.13)
project(ML_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(ML_1 main.cpp Parser.h IExpression.h BinOp.h Conjunction.h Disjunction.h Implication.h Variable.h Negate.h)