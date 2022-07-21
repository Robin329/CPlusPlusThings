cmake_minimum_required(VERSION 3.14)
project(cpp_principles_practice)

set(CMAKE_CXX_STANDARD 17)
include_directories(../../lib/magic_enum/include)
include_directories(../../lib)
include_directories(./../include)

add_executable(p205_book main.cpp Book.cpp Book.h Chrono.cpp Chrono.h Library.cpp Library.h
        Money.cpp Money.h Patron.cpp Patron.h Rational.cpp Rational.h)
add_executable(p205_ex13 p205_ex13.cpp Book.cpp Book.h Chrono.cpp Chrono.h Library.cpp Library.h
        Money.cpp Money.h Patron.cpp Patron.h Rational.cpp Rational.h)

add_executable(p205_ex14_ex16 p205_ex14_ex16.cpp Book.cpp Book.h Chrono.cpp Chrono.h Library.cpp Library.h
        Money.cpp Money.h Patron.cpp Patron.h Rational.cpp Rational.h)