cmake_minimum_required(VERSION 3.30)
project(UaiBank C)

set(CMAKE_C_STANDARD 11)

add_library(Vector SHARED
        vector/vector.h
        vector/vector.c
)
target_link_libraries(Vector PUBLIC Util)

add_library(FileUtil SHARED
        util/file_util.h
        util/file_util.c
)
target_link_libraries(FileUtil PUBLIC Vector User)

add_library(Util SHARED
        util/io_util.h
        util/io_util.c
        util/int_util.h
)

add_library(User SHARED
        user/user.h
        user/user.c
)
target_link_libraries(User PUBLIC Util)

add_executable(UaiBank
        main.c
        uai_bank/uai_bank.h
        uai_bank/uai_bank.c
)

target_link_libraries(UaiBank
        Vector
        FileUtil
        Util
        User
)

install(TARGETS Vector FileUtil Util User UaiBank
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include
)
