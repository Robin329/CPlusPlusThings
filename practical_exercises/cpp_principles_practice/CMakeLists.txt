cmake_minimum_required(VERSION 3.14)
project(cpp_principles_practice)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)
include_directories(./include)
include_directories(./Graphics)

if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(p32_1 Chapter2/p32_1.cpp)
    add_executable(p35_3.1_input Chapter3/p35_3.1_input.cpp)
    add_executable(p35_3.3_input Chapter3/p35_3.3_input.cpp)
    add_executable(p41_3.5.1_repeate Chapter3/p41_3.5.1_repeate.cpp)
    add_executable(p47_3.9.2_type_convert Chapter3/p47_3.9.2_type_convert.cpp)
    add_executable(p48_excercise Chapter3/p48_excercise.cpp)
    add_executable(p49_ex02 Chapter3/p49_ex02.cpp)
    add_executable(p49_bad_name Chapter3/p49_bad_name.cpp)
    add_executable(p49_ex04 Chapter3/p49_ex04.cpp)
    add_executable(p49_ex06 Chapter3/p49_ex06.cpp)
    add_executable(p49+ex07 Chapter3/p49_ex07.cpp)
    add_executable(p49_ex08 Chapter3/p49_ex08.cpp)
    add_executable(p50_ex10 Chapter3/p50_ex10.cpp)
    add_executable(p50_ex11 Chapter3/p50_ex11.cpp)

    add_executable(p59_trytry Chapter4/p59_trytry.cpp)
    add_executable(p63_tt_char_table Chapter4/p63_tt_char_table.cpp)
    add_executable(p66_tt Chapter4/p66_tt.cpp)
    add_executable(p67_4.6_vector Chapter4/p67_4.6_vector.cpp)
    add_executable(p70_4.6.3_text Chapter4/p70_4.6.3_text.cpp)
    add_executable(p71_tt Chapter4/p71_tt.cpp)
    add_executable(p71_ex01 Chapter4/p71_ex01.cpp)
    add_executable(p71_ex06 Chapter4/p71_ex06.cpp)
    add_executable(p72_ex02 Chapter4/p72_ex02.cpp)
    add_executable(p72_ex03 Chapter4/p72_ex03.cpp)
    add_executable(p72_ex04_guess_number Chapter4/p72_ex04_guess_number.cpp)
    add_executable(p73_ex05_calculator Chapter4/p73_ex05_calculator.cpp)
    add_executable(p73_ex06 Chapter4/p73_ex06.cpp)
    add_executable(p73_ex07 Chapter4/p73_ex07.cpp)
    add_executable(p73_ex08 Chapter4/p73_ex08.cpp)
    add_executable(p73_ex10 Chapter4/p73_ex10.cpp)
    add_executable(p73_ex11 Chapter4/p73_ex11.cpp)
    add_executable(p73_ex15 Chapter4/p73_ex15.cpp)
    add_executable(p73_ex16 Chapter4/p73_ex16.cpp)
    add_executable(p73_ex17 Chapter4/p73_ex17.cpp)
    add_executable(p73_ex18 Chapter4/p73_ex18.cpp)
    add_executable(p74_ex19 Chapter4/p74_ex19.cpp)
    add_executable(P74_ex20 Chapter4/p74_ex20.cpp)

    # Chapter4
    add_executable(p83_tt Chapter5/p83_tt1.cpp)
    target_link_libraries(p83_tt gtest gtest_main pthread)

    # Chapter6
    add_executable(p128_tt_calculator Chapter6/p128_tt_calculator.cpp)
    add_executable(p129_tt1 Chapter6/p129_tt1.cpp)
    add_executable(p129_ex05 Chapter6/p129_ex05.cpp)
    add_executable(p129_ex08 Chapter6/p129_ex08.cpp)
    add_executable(p129_ex09 Chapter6/p129_ex09.cpp)
    add_executable(p129_ex10 Chapter6/p129_ex10.cpp)

    # Chapter7
    add_executable(p151_calculator08buggy_ex1 Chapter7/p151_calculator08buggy_ex1.cpp)
    add_executable(p151_ex Chapter7/p151_ex.cpp)
    add_executable(p151_ex10 Chapter7/p151_ex10.cpp)

    # Chapter8
    add_executable(my Chapter8/ex01/use.cpp Chapter8/ex01/my.cpp Chapter8/ex01/my.h)
    add_executable(p180_ex02 Chapter8/p180_ex02.cpp)
    add_executable(p180_ex03 Chapter8/p180_ex03.cpp)
    add_executable(p181_ex01 Chapter8/p181_ex01.cpp)
    add_executable(p181_ex02 Chapter8/p181_ex02.cpp)
    add_executable(p181_ex03 Chapter8/p181_ex03.cpp)
    add_executable(p181_ex04 Chapter8/p181_ex04.cpp)
    add_executable(p181_ex05 Chapter8/p181_ex05.cpp)
    add_executable(p181_ex08 Chapter8/p181_ex08.cpp)
    add_executable(p181_ex09 Chapter8/p181_ex09.cpp)
    add_executable(p181_ex11 Chapter8/p181_ex11.cpp)
    add_executable(p181_ex13 Chapter8/p181_ex13.cpp)

    # Chapter9
    # add_executable(p202_ex05 Chapter9/p202_ex05.cpp)
    # add_executable(p205_ex02 Chapter9/p205_ex02.cpp)
    # add_subdirectory(Chapter9/p205_ex05_ex09)
    add_subdirectory(Chapter12)

    # Chapter10
    add_executable(p212_read_write_file Chapter10/p212_read_write_file.cpp)
    set(PATTERNS
        Chapter10
        Chapter11
        Chapter17
        Chapter18
        Chapter19
    )

    foreach(_dir IN ITEMS ${PATTERNS})
        file(GLOB _files "${_dir}/*.cpp")

        # message(STATUS "Pattern `${_dir}':")
        foreach(_file IN ITEMS ${_files})
            get_filename_component(_file_name
                ${_file} NAME
            )
            set(_project_name "${_file_name}")

            # message(STATUS "  ${_dir}/${_file_name} is going to be built")
            add_executable(${_project_name} "${_dir}/${_file_name}")
        endforeach()
    endforeach()
endif()