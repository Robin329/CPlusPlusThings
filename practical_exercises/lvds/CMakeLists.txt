cmake_minimum_required(VERSION 3.14)
project(lvds_rgb_format)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)

add_executable(lvds_format jeida_vesa.cpp)