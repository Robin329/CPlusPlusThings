cmake_minimum_required(VERSION 3.14)
project(self_lear)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include/armadillo)

add_executable(1.spline_interpolation 1.spline_interpolation/1.spline_interpolation.cpp)
add_definitions(-DARMA_DONT_USE_WRAPPER)
find_library(1.spline_interpolation /usr/local/lib/)
#target_link_libraries(1.spline_interpolation armadillo)
#target_link_libraries(1.spline_interpolation mlpack)