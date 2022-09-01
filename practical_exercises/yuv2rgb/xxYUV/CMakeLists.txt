cmake_minimum_required(VERSION 3.14)
project(yuv_rgb)

add_executable(yuv_rgb apple_amx.h cpu.cpp cpu.h rgb2yuv.cpp rgb2yuv.h rgb2yuv.inl yuv.h yuv2rgb.cpp yuv2rgb.h)