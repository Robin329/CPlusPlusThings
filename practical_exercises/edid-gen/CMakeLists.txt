cmake_minimum_required(VERSION 3.14)
project(edid-gen)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(./include)

aux_source_directory(./ SRC_MAIN)
add_executable(edidgen edid_gen.c)
