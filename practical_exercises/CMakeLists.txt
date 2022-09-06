cmake_minimum_required(VERSION 3.14)
project(key_exercises)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(../lib/json-develop/include)
add_executable(20.magic_enum_example key_exercises/20.magic_enum_example.cpp)
add_executable(conversion_func key_exercises/1.conversion_func.cpp)
add_executable(2.bracket_overload key_exercises/2.bracket_overload.cpp)
add_executable(3.function_template key_exercises/3.function_template.cpp)
add_executable(4.dynamic_array key_exercises/4.dynamic_array.cpp)
add_executable(7.load_settings key_exercises/7.load_setting.cpp key_exercises/7.382_reg.h)
target_link_libraries(4.dynamic_array gtest gtest_main pthread)
add_executable(5.Dictionary_insertion_and_lookup key_exercises/5.Dictionary_insertion_and_lookup.cpp)
add_executable(19.StringSplitCpp key_exercises/19.StringSplitCpp.cpp)
add_executable(6.timer_clock key_exercises/6.timer_clock.cpp)
add_executable(8.array_of_class_temp key_exercises/8.Array_of_class_template_specialization.cpp)
add_executable(9.casting_Of_operator_overloading key_exercises/9.Casting_of_operator_overloading.cpp)
add_executable(10.clock++_operator_ov key_exercises/10.Clock++_operator_overloading.cpp)
add_executable(11.clock_with_overloaded_par key_exercises/11.Clock_with_overloaded_parentheses.cpp)
add_executable(12.exception_catch key_exercises/12.Exception_catch.cpp)
add_executable(13.inheritance_encap key_exercises/13.Inheritance_encapsulation.cpp)
add_executable(14.input_and_output_operator key_exercises/14.Input_and_output_operator_overloading.cpp)
add_executable(15.input_and_output_overload key_exercises/15.Input_and_output_overload.cpp)
add_executable(16.output_format key_exercises/16.Output_format.cpp)
add_executable(17.readwrite_files key_exercises/17.readwrite_files.cpp)
add_executable(18.stack_of_class_templates key_exercises/18.Stack_of_class_templates.cpp)
add_executable(21.MultiDimensionalArray key_exercises/21.MultiDimensionalArray.cpp)
add_executable(31.memset_struct_class key_exercises/31.memset_struct_class.cpp)
add_executable(32.convert_picture_to_hex key_exercises/32.convert_picture_to_hex.cpp)
add_executable(33.num_convert_negative key_exercises/33.num_convert_negative.cpp)

if(CMAKE_HOST_APPLE)
    find_package(OpenCV)
    include_directories(${OpenCV_INCLUDE_DIRS})
    include_directories("/usr/local/Cellar/opencv/4.5.1_3/include/opencv4/")

    # ----------------------------------------------------------
    # add libs you need
    set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_calib3d)

    # or add all
    # include_directories(${OpenCV_INCLUDE_DIRS})
    set(OpenCV_DIR "/usr/local/Cellar/opencv/4.5.2/include/opencv4/opencv2/")
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})

    # linking
    # target_link_libraries(RAII ${OpenCV_LIBS})
endif()

add_executable(23.average_method key_exercises/23.average_method.cpp)
add_executable(24.cjson_parse key_exercises/25.cjson_parse.cpp)

add_executable(timerfunc timerfunc/timer.cpp timerfunc/timer.h timerfunc/alarm_timer.cpp timerfunc/alarm_timer.h timerfunc/main.cpp)
target_link_libraries(timerfunc -lpthread)

# interview test
add_executable(is_point_inside_triangle interview_test/is_point_inside_triangle.cpp)
add_executable(interview_test_volatile interview_test/volatile.cpp)

if(CMAKE_HOST_APPLE)
    # cpp Principles and Practice
    add_subdirectory(cpp_principles_practice)
endif()

# looper and handler
add_subdirectory(looper_handler)

add_executable(26.compare_two_file key_exercises/26.compare_two_files.cpp)
add_executable(27.is_float_or_int key_exercises/27.is_float_or_int.cpp)
add_executable(28.check_Big_Little_endian key_exercises/28.check_Big_Little_endian.cpp)
add_executable(29.malloc key_exercises/29.malloc.cpp)
add_executable(30.two_dimensional_array_convert key_exercises/30.two_dimensional_array_convert.cpp)
add_executable(31.data_type_range key_exercises/31.data_type_range.cpp)

# epoll
if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux" OR "ubuntu")
    # epoll
    add_executable(epoll_sample.cpp epoll/epoll_sample.cpp)
    add_executable(epoll.c epoll/epoll.c)

    # socket
    add_executable(socket_test socket/socket_test.cpp socket/socket.h socket/socket.cpp)
    target_link_libraries(socket_test gtest gtest_main pthread)
endif()

# share memory
add_subdirectory(share_memory)

# callback func
add_subdirectory(callback)

# crc test
add_subdirectory(crc)

# VESA DMT/CTA-861-G
add_subdirectory(edidvic)

# yuv2rgb
add_subdirectory(yuv2rgb)