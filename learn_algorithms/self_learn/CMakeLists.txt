cmake_minimum_required(VERSION 3.14)
project(self_lear)

set(CMAKE_CXX_STANDARD 17)
include_directories(../../lib)
include_directories(../../lib/magic_enum/include)
# include_directories(/usr/local/include/armadillo)

add_executable(1.spline_interpolation 1.spline_interpolation/1.spline_interpolation.cpp)

add_executable(2.spline_keystone 1.spline_interpolation/2.spline_keystone.cpp)

if (CMAKE_HOST_APPLE)
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

    add_executable(2.helen_formula 2.helen_formula/2.helen_formula.cpp)
    target_link_libraries(2.helen_formula ${OpenCV_LIBS})
endif()