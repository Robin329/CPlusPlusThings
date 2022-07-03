cmake_minimum_required(VERSION 3.14)
project(cpp_principles_practice)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(./include)
include_directories(./Graphics)

if(CMAKE_HOST_APPLE)
    add_library(libfltk.a STATIC IMPORTED)
    set(FLTK_DIR "/usr/local/include")
    include_directories(${FLTK_DIR})
    include_directories(/usr/local/lib)

    # find_library(FLTK_FOUND /usr/local/lib)
    if($(FLTK_FOUND))
        message("fltk ----------->> found!!!")
    else()
        message("fltk ----------->> NOT found!!!")
    endif()

    # add_executable(p251_drill01.cpp ./p251_drill01.cpp ../Graphics/Graph.cpp ../Graphics/GUI.cpp ../Graphics/Window.cpp)
    # target_link_libraries(p251_drill01.cpp /usr/local/lib/libfltk.a /usr/local/lib/libfltk_forms.a
    # /usr/local/lib/libfltk_gl.a /usr/local/lib/libfltk_png.a /usr/local/lib/libfltk_jpeg.a /usr/local/lib/libfltk_images.a)
endif()