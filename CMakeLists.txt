cmake_minimum_required(VERSION 3.30)
project(UaiBank C)

set(CMAKE_C_STANDARD 11)

add_executable(UaiBank
        vector/vector.h vector/vector.c
        util/int_util.h
        util/file_util.h
        util/file_util.c
        main.c
        user/user.h
        user/user.c
)

