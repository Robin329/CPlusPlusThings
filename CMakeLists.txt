cmake_minimum_required(VERSION 3.16)
project(CPlusPlusThings)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/include/")
#add_executable(CPlusPlusThings main.cpp)
################################
#basic_content
################################
add_subdirectory(basic_content)

################################
#codingStyleldIoms
################################
add_subdirectory(codingStyleIdioms)
################################
#concurrency
################################
add_subdirectory(concurrency/Threading_In_CPlusPlus)

################################
#design_pattern
################################
add_executable(producer_consumer design-patterns-cpp/producer_consumer/producer_consumer.cpp)
target_link_libraries(producer_consumer -lpthread)


################################
#effective_c++
################################

################################
#gtest
################################
add_executable(cpp_test gtest/cpp_test/cpp_test.cpp)
target_link_libraries(cpp_test gtest gtest_main pthread)
add_executable(base_test lib/base_test.cpp lib/base.cpp)
target_link_libraries(base_test gtest gtest_main pthread)

################################
#learn_class/modern_C++_30
################################
add_executable(rvalue learn_class/modern_C++_30/RAII/rvalue.cpp)
add_executable(heap learn_class/modern_C++_30/RAII/heap.cpp)
add_executable(container learn_class/modern_C++_30/container1/container.cpp)
add_executable(vector_l learn_class/modern_C++_30/container1/vector_l.cpp)
#add_executable(cpulpuls11_singleton learn_class/modern_C++_30/memorymodel_atomic/cpulpuls11_singleton.cpp)
add_executable(function learn_class/modern_C++_30/functionLambda/function.cpp)

add_executable(factorial1 learn_class/modern_C++_30/compilercompute/factorial.cpp)

################################
#c++2.0/c++11
################################
add_subdirectory(c++2.0/c++11)



################################
#leetcode
################################
#add_executable(1_Inverted_bits leetcode/1_Inverted_bits.cpp)
#add_executable(1.1_invertd_Integer leetcode/1.1_invertd_Integer.cpp)
#add_executable(3Sum leetcode/algorithms/cpp/3Sum/3Sum.cpp)
#add_executable(3SumClosest leetcode/algorithms/cpp/3SumClosest/3SumClosest.cpp)
#add_executable(addBinary leetcode/algorithms/cpp/addBinary/addBinary.cpp)
add_subdirectory(leetcode/algorithms/cpp)
################################
#thread_example
################################
add_subdirectory(thread_example)

################################
#practical_exercises
################################
add_subdirectory(practical_exercises)

################################
#practical_exercises/primer_cpp_6
################################
add_subdirectory(practical_exercises/primer_cpp_6)
add_subdirectory(practical_exercises/primer_cpp_5)

add_executable(template learn_class/modern_C++_30/compilerpoly/template.cpp)

include_directories(lib/json-develop)
add_subdirectory(lib/json-develop)
add_subdirectory(learn_class/modern_C++_30)
add_subdirectory(C-Plus-Plus)
add_subdirectory(design-patterns-cpp)
add_subdirectory(lib/json-develop/test)
add_subdirectory(practical_exercises/10_day_practice)

find_package(Threads REQUIRED)
target_link_libraries(thread_test
        ${CMAKE_THREAD_LIBS_INIT} pthread)
target_link_libraries(mutex_demo
        ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(thread_param
        ${CMAKE_THREAD_LIBS_INIT} pthread)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(stl_map src_analysis/stl/stl_src/Containers/stl_map.cpp)


if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(googletest-distribution)
set(GOOGLETEST_VERSION 1.10.0)

if (CMAKE_VERSION VERSION_GREATER "3.0.2")
    if (NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
        set(CMAKE_CXX_EXTENSIONS OFF)
    endif ()
endif ()

enable_testing()

include(CMakeDependentOption)
include(GNUInstallDirs)

#Note that googlemock target already builds googletest
option(BUILD_GMOCK "Builds the googlemock subproject" ON)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" ON)

if (BUILD_GMOCK)
    add_subdirectory(gtest/googlemock)
else ()
    add_subdirectory(gtest/googletest)
endif ()

set(BASE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
# googletest
set(GTEST_INCLUDE_DIR ${BASE_INCLUDES}/gtest/googletest/include)
set(GMOCK_INCLUDE_DIR ${BASE_INCLUDES}/gtest/googlemock/include)

# 去哪里找头文件 相当于gcc/clang 中的-I(i的大写字母)参数
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${GMOCK_INCLUDE_DIR})

# 去哪里找库文件 .so .dll .dylib 相当于gcc 中的-L参数
link_directories(${GTEST_LINK_DIR})
link_directories(${GMOCK_LINK_DIR})

set(BASE_LIB_DIR ${BASE_INCLUDES}/lib)

include_directories(${BASE_LIB_DIR})

set(MAGIC_ENUM_DIR ${BASE_INCLUDES}/lib/magic_enum)
include_directories(${MAGIC_ENUM_DIR}/include)
#MESSAGE("base lib dir = ${BASE_LIB_DIR} ${BASE_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}")
#add_executable(RAII ${SOURCE_FILES})
#######################json lib#######################
set(JSON_INCLUDE_DIR ${BASE_INCLUDES}/lib/json/include)
set(JSON_SINGLE_INCLUDE_DIR ${BASE_INCLUDES}/lib/json/single_include)
link_directories(${JSON_INCLUDE_DIR})
link_directories(${JSON_SINGLE_INCLUDE_DIR})
include_directories(${JSON_INCLUDE_DIR})
include_directories(${JSON_SINGLE_INCLUDE_DIR})
#######################json lib#######################

#######################OPENCV SETTING#######################
#target_link_libraries(RAII ${OpenCV_LIBS})
#----------------------------------------------------------
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/local/Cellar/opencv/4.5.1_3/include/opencv4/")
#----------------------------------------------------------
# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_calib3d)
# or add all
# include_directories(${OpenCV_INCLUDE_DIRS})

set(OpenCV_DIR "/usr/local/Cellar/opencv/4.5.2/include/opencv4/opencv2/")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# linking
#target_link_libraries(RAII ${OpenCV_LIBS})

add_executable(homography_2d practical_exercises/opencv/homography_2d.cpp)
target_link_libraries(homography_2d ${OpenCV_LIBS})
###############################################################

#ADD_DEFINITIONS(-DOPENCV_ENABLE_NONFREE)



#----------------------------------------------------------------------
set(CHAPTERS
        basic_content
        c++2.0
        concurrency
        design_pattern
        effective_c++
        learn_class
        leetcode
        practical_exercises
        src_analysis
        thread_example)
set(basic_content
        func_pointer
        maohao
        virtual
        volatile)
#basec_content/virtual
set(virtual
        set1
        set2
        set3
        set4)
set(c++2.0
        c++11
        )

set(set2
        default_arg
)
set(set3
        full_virde
        vir_con
        vir_de
        virtual_inline
        virtual_function
        virtual_function1)
#basec_content/virtual/set4
set(set4
        rtti
        )
foreach(CHAPTER ${CHAPTERS})
    foreach(DEMO ${${CHAPTER}})
        foreach(SUB1 ${${DEMO}})
            foreach(SUB2 ${${SUB1}})
#                message("DEMO -->${DEMO}")
#                message("SUB2 -->${SUB2}")
#                message("SUB1 -->${SUB1}")
                file(GLOB SOURCE
                        "${CHAPTER}/${DEMO}/*.h"
                        "${CHAPTER}/${DEMO}/*.cpp"
                        "${CHAPTER}/${DEMO}/*.c"
                        "${CHAPTER}/${DEMO}/${SUB1}/${SUB2}.c"
                        "${CHAPTER}/${DEMO}/${SUB1}/${SUB2}.cpp"
                        "${CHAPTER}/${DEMO}/${SUB1}/${SUB2}.cpp"
                        )
#                message("SOURCE -->${SOURCE}")
                set(NAME "${CHAPTER}_${DEMO}_${SUB2}")
#                message("NAME -->${NAME}")
                add_executable(${NAME} ${SOURCE})
            endforeach(SUB2)
        endforeach(SUB1)
    endforeach(DEMO)
endforeach(CHAPTER)
