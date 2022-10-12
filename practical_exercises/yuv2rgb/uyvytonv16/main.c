//
//  main.c
//  UyvyToNv16
//
//  Created by robin.jiang on 10/13
//  Copyright (c) 2022 robin.jiang. All rights reserved.
//

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "UyvyToNv16.h"

#define MAX_WIDTH  7680
#define MAX_HEIGHT 4320

static uint8_t img[MAX_WIDTH * MAX_HEIGHT * 2];
static uint8_t y_dst[MAX_WIDTH * MAX_HEIGHT];
static uint8_t u_et_v_dst[MAX_WIDTH * MAX_HEIGHT];

int main(int argc, const char *argv[]) {
    int ifd;
    int ofd;

    size_t rd_sz;

    uint32_t width;
    uint32_t height;
    uint32_t wxh;

    char *cp;
    char  output[256] = {0};

    if (argc < 4) {
        fprintf(stderr, "useage: %s [input_file] [width] [height]\n", argv[0]);

        return -1;
    }

    rd_sz = 0;
    width = 0;
    height = 0;
    wxh = 0;
    cp = NULL;

    // get input file name from comand line
    ifd = open(argv[1], O_RDONLY);
    if (ifd < 0) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    // specify output file name
    cp = strrchr(argv[1], '.');
    strncpy(output, argv[1], cp - argv[1]);
    strcat(output, "_nv16");
    strcat(output, cp);

    ofd = open(output, O_WRONLY | O_CREAT, S_IRUSR);

    width = atoi(argv[2]);
    height = atoi(argv[3]);

    wxh = width * height;

    fprintf(stderr, "Processing: ");

    while (1) {
        rd_sz = read(ifd, img, wxh * 2);

        if (rd_sz == wxh * 2) {
            unpack(wxh, (uint32_t *)y_dst, (uint32_t *)u_et_v_dst, img);
            write(ofd, y_dst, wxh);
            write(ofd, u_et_v_dst, wxh);
        } else {
            break;
        }
        fputc('.', stderr);
        fflush(stderr);
    }

    close(ifd);
    close(ofd);

    fprintf(stderr, "Done\n");
    fprintf(stderr, "Output file: %s\n", output);

    return 0;
}
