cmake_minimum_required(VERSION 3.30)
project(UaiBank C)

set(CMAKE_C_STANDARD 11)

add_executable(UaiBank
        user/user.h user/user.c
        vector/vector.h vector/vector.c
        util/file_util.h util/file_util.c
        util/int_util.h
        main.c
)

