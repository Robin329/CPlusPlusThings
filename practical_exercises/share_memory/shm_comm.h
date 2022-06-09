
#pragma once
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define PATHNAME \
    "/home/ubuntu/workspace/CPlusPlusThings/practical_exercises/share_memory/shmfile" //路径名

#define PROJ_ID 0x6666 //整数标识符
#define SIZE 4096      //共享内存的大小