#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "file_utils.h"
#include "fill_yuvdata.h"

// 8����������������ɫ���ܴ�λ
#define WIDTH 720
#define HEGHT 480

// yuv422��w*h*2
// yuv420��w*h*3/2
#define FILE_SIZE (WIDTH * HEGHT * 3 / 2)

int main(void) {
    printf("test of writing yuv...\n");
    unsigned char* buffer = (unsigned char*)malloc(FILE_SIZE);
    // ok
    // fill_yuv_uyvy_2(buffer, WIDTH, HEGHT);
    // ok
    // fill_yuv_yuv422_2(buffer, WIDTH, HEGHT);
    // _1 ok _2 not ok
    fill_yuv_yuv420_2(buffer, WIDTH, HEGHT);
    write_file("yuv.yuv", (char*)buffer, FILE_SIZE);
    return 0;
}