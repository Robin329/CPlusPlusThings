cmake_minimum_required(VERSION 3.14)
project(scrambler-demo)

# https://github.com/crioux/edidvic
set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../../lib)

add_executable(dp_scramble DPScramble.h lfsr.cpp lfsr.h scrambler_hbrx_rbr.cpp)
