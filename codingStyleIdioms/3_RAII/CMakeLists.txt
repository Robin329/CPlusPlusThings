cmake_minimum_required(VERSION 3.14)
project(Threading_In_CPlusPlus)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/local/Cellar/opencv/4.5.1_3/include/opencv4/")
# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_calib3d)
# or add all
# include_directories(${OpenCV_INCLUDE_DIRS})

set(OpenCV_DIR "/usr/local/Cellar/opencv/4.5.2/include/opencv4/opencv2/")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(c++_example.cpp c++_example.cpp)
add_executable(c++_example1.cpp c++_example1.cpp)
add_executable(c++_example2.cpp c++_example2.cpp)
add_executable(c_example.cpp c_example.cpp)
add_executable(RAII.cpp RAII.cpp)
target_link_libraries(RAII.cpp ${OpenCV_LIBS})
add_executable(RAII_fstram.cpp RAII_fstram.cpp)