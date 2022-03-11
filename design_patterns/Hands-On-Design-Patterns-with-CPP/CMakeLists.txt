cmake_minimum_required(VERSION 3.5)

project(Hands-On-Design-Patterns)

#find_package(benchmark REQUIRED)

add_executable(4.list_swap.c Chapter04/list_swap.C)
add_executable(5.mutex1.c Chapter05/mutex1.C)
target_link_libraries(5.mutex1.c gtest gtest_main pthread)
add_executable(5.memory1.c Chapter05/memory1.C)
target_link_libraries(5.memory1.c gtest gtest_main pthread)

#add_executable(6.smartptr.c Chapter06/smartptr.C)
#target_link_libraries(6.smartptr.c benchmark::benchmark)