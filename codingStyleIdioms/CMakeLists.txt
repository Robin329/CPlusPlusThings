cmake_minimum_required(VERSION 3.14)
project(Morden_C++)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(1_classInitializers)
add_executable(2_enumclass 2_enumclass/namespace.cpp)
add_subdirectory(3_RAII)
add_executable(4_copy-swap 4_copy-swap/copy-swapAndADL.cpp)
add_executable(5_no_pimpl 5_pImpl/noPimpl.cpp)
add_executable(5_pimpl 5_pImpl/pimpl.cpp)
add_executable(5_pimpl_time 5_pImpl/pimplTime.cpp 5_pImpl/pimplTime.h)