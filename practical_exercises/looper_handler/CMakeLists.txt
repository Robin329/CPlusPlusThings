cmake_minimum_required(VERSION 3.14)
project(looper_handler)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(.)
include_directories(../../googletest/googletest/include/gtest/)
#
# example
#
add_executable(loop_example loop.cpp loop.h example.cpp)
target_link_libraries(loop_example pthread)


#
# test
#
add_executable(ahandler_test test/ahandler_test.cpp loop.cpp loop.h)
target_link_libraries(ahandler_test gtest gtest_main pthread)
add_executable(amessage_test test/amessage_test.cpp loop.cpp loop.h)
target_link_libraries(amessage_test gtest gtest_main pthread)
add_executable(loop_test test/test.cpp loop.cpp loop.h)
target_link_libraries(loop_test gtest gtest_main pthread)