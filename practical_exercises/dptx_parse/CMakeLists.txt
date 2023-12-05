cmake_minimum_required(VERSION 3.14)
project(dptx_parse)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(./)

aux_source_directory(./ SRC_MAIN)
add_executable(dptx_parse dptx_parse.c)
