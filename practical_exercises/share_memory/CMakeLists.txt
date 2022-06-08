cmake_minimum_required(VERSION 3.14)
project(key_exercises)

set(CMAKE_CXX_STANDARD 17)
include_directories(../lib/magic_enum/include)
include_directories(../lib)

if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    add_executable(share_memory_read read.c)
    add_executable(share_memory_write write.c)
    # pipe
    add_executable(share_memory_pipe pipe.c)
    add_executable(share_memory_pipe_test pipe_test.c)
    add_executable(share_memory_pipe_size pipe_size.c)
    # pipe fifo
    add_executable(share_memory_pipe_fifo pipe_fifo.c)
    # pipe fifo server <-> client
    add_executable(share_memory_pipe_fifo_server pipe_fifo_server.c pipe_fifo_comm.h)
    add_executable(share_memory_pipe_fifo_client pipe_fifo_client.c pipe_fifo_comm.h)
    add_executable(share_memory_pipe_fifo_server_calc pipe_fifo_server_calc.c pipe_fifo_comm.h)
    add_executable(share_memory_pipe_fifo_server_system_cmd pipe_fifo_server_system_cmd.c pipe_fifo_comm.h)
    # pipe fifo rw file
    add_executable(share_memory_pipe_fifo_server_rw pipe_fifo_server_rw.c pipe_fifo_comm.h)
    add_executable(share_memory_pipe_fifo_client_rw pipe_fifo_client_rw.c pipe_fifo_comm.h)
    # share memory
    add_executable(shm shm.c)
    add_executable(shmctl shmctl.c)
    add_executable(shmat shmat.c)
    add_executable(shmdt shmdt.c)
    # share memory server<->client
    add_executable(shm_server shm_server.c shm_comm.h)
    add_executable(shm_client shm_client.c shm_comm.h)
endif()