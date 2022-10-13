cmake_minimum_required(VERSION 3.14)
project(yuv2rgb)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)

if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux" OR "ubuntu")
    # add_subdirectory(xxYUV)
add_subdirectory(yuv2rgb_c99)
add_subdirectory(uyvytonv16)
add_subdirectory(cpp-rgb2yuv)
endif()