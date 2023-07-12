cmake_minimum_required(VERSION 3.14)
project(callback_func)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(.)
include_directories(../../gtest/googletest/include/gtest)

add_executable(callback_func callback_func.cpp)
add_executable(callback_func_pro callback_func_pro.cpp)
add_executable(callback_lambda callback_lambda.cpp)
add_executable(callback_convert callback_convert.cpp)