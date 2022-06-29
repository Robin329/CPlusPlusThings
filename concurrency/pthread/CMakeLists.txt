cmake_minimum_required(VERSION 3.14)
project(pthread_example)

set(CMAKE_CXX_STANDARD 17)
include_directories(../../lib/magic_enum/include)
include_directories(../../lib)
include_directories(/usr/include)

# pthread set sched policy
add_executable(pthread_fifo pthread_attr_setschedpolicy_fifo.c pthread_common.h posixtest.h affinity.h)
target_link_libraries(pthread_fifo pthread)

add_executable(pthread_rr pthread_attr_setschedpolicy_rr.c pthread_common.h posixtest.h affinity.h)
target_link_libraries(pthread_rr pthread)

add_executable(pthread_other pthread_attr_setschedpolicy_other.c pthread_common.h posixtest.h affinity.h)
target_link_libraries(pthread_other pthread)

add_executable(pthread_all pthread_attr_setschedpolicy.c pthread_common.h posixtest.h affinity.h)
target_link_libraries(pthread_all pthread)

# timers
add_executable(twoevtimers timers/twoevtimers.c posixtest.h)
target_link_libraries(twoevtimers rt)

add_executable(twoptimers timers/twoptimers.c posixtest.h)
target_link_libraries(twoptimers rt)

#  pthread brarrier
add_executable(pthread_barrier pthread_barrier.cpp)
target_link_libraries(pthread_barrier pthread)
