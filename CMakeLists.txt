cmake_minimum_required(VERSION 3.30)
project(Trabalho_Pratico C)

set(CMAKE_C_STANDARD 11)

add_executable(UaiBank main.c
        vector/vector.h vector/vector.c
        int_util.h)
