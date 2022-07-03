cmake_minimum_required(VERSION 3.14)
project(pthread_example)

set(CMAKE_CXX_STANDARD 17)
include_directories(lib/magic_enum/include)
include_directories(lib)
include_directories(/usr/include)

add_subdirectory(Threading_In_CPlusPlus)
add_subdirectory(thread_example)
add_subdirectory(concurrency_v1)

if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux" OR "ubuntu")
    add_subdirectory(pthread)
    add_subdirectory(process)
endif()
