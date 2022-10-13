cmake_minimum_required(VERSION 3.14)
project(yuv2rgb_head)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../../../lib)
include_directories(./include)

add_executable(cpp-rgb2yuv test/test.cpp test/stopwatch.hpp test/detect_plat.hpp)