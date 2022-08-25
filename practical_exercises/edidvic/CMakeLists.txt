cmake_minimum_required(VERSION 3.14)
project(crc-=test)

# https://github.com/crioux/edidvic
set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(./include)

aux_source_directory(./ SRC_MAIN)
add_executable(edidvic edidvic.c vic_timings.h)

# SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
# add_library(libcrc STATIC ${SRC_MAIN})