cmake_minimum_required(VERSION 3.14)
project(Morden_C++)

set(CMAKE_CXX_STANDARD 17)
add_executable(what_is_stl stl/stl_src/what_is_stl.cpp)
add_executable(unique_ptr stl/stl_src/Ptr/unique_ptr.cpp)