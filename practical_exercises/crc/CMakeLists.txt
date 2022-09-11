cmake_minimum_required(VERSION 3.14)
project(crc_test)

# https://github.com/gityf/crc/tree/master/crc
set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(./include)

aux_source_directory(./ SRC_MAIN)
add_executable(crc_test crc16.cpp crc16.h crc32.c crc32.h crc64.c crc64.h crc8.c crc8.h crc_poly.c crc_poly.h crchash.cpp crchash.h test_crc.cpp test_harness.h test_harness.cpp)
target_link_libraries(crc_test gtest gtest_main pthread)

# SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
# add_library(libcrc STATIC ${SRC_MAIN})