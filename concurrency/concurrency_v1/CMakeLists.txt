cmake_minimum_required(VERSION 3.14)
project(concurrency_v1)

set(CMAKE_CXX_STANDARD 17)

add_executable(2.1_basic chapter2/2.1_basic.cpp)
target_link_libraries(2.1_basic -lpthread)
add_executable(2.2_transfer chapter2/2.2_transfer.cpp)
target_link_libraries(2.2_transfer  -lpthread)
add_executable(2.3_ownership chapter2/2.3_ownership.cpp)
target_link_libraries(2.3_ownership  -lpthread)