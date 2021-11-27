# Note: CMake support is community-based. The maintainers do not use CMake
# internally.

cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(googletest-distribution)
set(GOOGLETEST_VERSION 1.10.0)

if (CMAKE_VERSION VERSION_GREATER "3.0.2")
  if(NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
    set(CMAKE_CXX_EXTENSIONS OFF)
  endif()
endif()

enable_testing()

# add opencv lib
find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

include(CMakeDependentOption)
include(GNUInstallDirs)

#Note that googlemock target already builds googletest
option(BUILD_GMOCK "Builds the googlemock subproject" ON)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" ON)

if(BUILD_GMOCK)
  add_subdirectory( googlemock )
else()
  add_subdirectory( googletest )
endif()
# googletest
set(GTEST_INCLUDE_DIR ${BASE_INCLUDES}/gtest/googletest/include)
set(GMOCK_INCLUDE_DIR ${BASE_INCLUDES}/gtest/googlemock/include)
set(GTEST_LINK_DIR ${BASE_LIBS}/gtest/lib/)
set(GMOCK_LINK_DIR ${BASE_LIBS}/gmock/lib/)

# 去哪里找头文件 相当于gcc/clang 中的-I(i的大写字母)参数
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${GMOCK_INCLUDE_DIR})

# 去哪里找库文件 .so .dll .dylib 相当于gcc 中的-L参数
link_directories(${GTEST_LINK_DIR})
link_directories(${GMOCK_LINK_DIR})

add_executable(cpp_test gtest/cpp_test/cpp_test.cpp)
target_link_libraries(cpp_test gtest gtest_main pthread)