
#pragma once
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define PATHNAME \
    "/home/ubuntu/workspace/CPlusPlusThings/practical_exercises/share_memory/shmfile" //路径名

#define PROJ_ID 0x6666 //整数标识符
#define SIZE 4096      //共享内存的大小