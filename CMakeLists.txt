cmake_minimum_required(VERSION 3.29)
project(unix_network_programming C)

set(CMAKE_C_STANDARD 99)

add_executable(daytime_tcp_client chapter_1/daytime_tcp_client.c
        chapter_1/daytime_tcp_server.c)
add_executable(daytime_tcp_server chapter_1/daytime_tcp_server.c)
