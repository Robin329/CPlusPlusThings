#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE_NAME "myfifo" //让客户端和服务端使用同一个命名管道
