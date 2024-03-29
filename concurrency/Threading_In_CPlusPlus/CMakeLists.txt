cmake_minimum_required(VERSION 3.14)
project(Threading_In_CPlusPlus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(intro 1.thread/intro.cpp)
add_executable(1.thread 1.thread/thread.cpp)
add_executable(1.three_threads 1.thread/three_threads.cpp)

add_executable(1.function_pointer 2.create_type/1.function_pointer.cpp)
add_executable(2.lambda_function 2.create_type/2.lambda_function.cpp)
add_executable(3.functor 2.create_type/3.functor.cpp)
add_executable(4.static_member_function 2.create_type/4.no_static_member_function.cpp)
add_executable(5.static_member_function 2.create_type/5.static_member_function.cpp)
add_executable(join 3.join_detach/join.cpp)
add_executable(detach 3.join_detach/detach.cpp)
add_executable(critical_section 4.mutex/critical_section.cpp)

add_executable(mutex_try_lock.cpp 4.mutex/mutex_try_lock.cpp)
add_executable(5.condition_variable 5.condition_variable/condition_variable_example.cpp)
add_executable(6.future_example 6.future/future_examples.cpp)

add_executable(4.semaphore 4.mutex/semaphore.cpp)
target_link_libraries(4.semaphore -lpthread)