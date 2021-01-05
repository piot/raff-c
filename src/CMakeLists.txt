cmake_minimum_required(VERSION 3.17)
project(raff C)

set(CMAKE_C_STANDARD 99)

set(deps ../deps/)


file(GLOB_RECURSE deps_src FOLLOW_SYMLINKS
        "${deps}*/src/lib/*.c"
        )

file(GLOB_RECURSE lib_src FOLLOW_SYMLINKS
        "lib/*.c"
        )

add_library(raff
    ${deps_src}
    ${lib_src}
    examples/main.c
)

target_include_directories(raff PRIVATE ${deps}clog/src/include)
target_include_directories(raff PRIVATE ${deps}tiny-libc/src/include)
target_include_directories(raff PUBLIC include)

target_compile_options(raff PRIVATE -Wall -Wno-unused-variable)

target_link_libraries(raff m)