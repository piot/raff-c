cmake_minimum_required(VERSION 3.17)
project(raff C)

set(CMAKE_C_STANDARD 11)

set(deps ../deps/)

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(COMPILER_NAME "clang")
    set(COMPILER_CLANG 1)
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_NAME "gcc")
    set(COMPILER_GCC 1)
elseif (CMAKE_C_COMPILER_ID STREQUAL "Intel")
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
endif()


if (DEFINED PLATFORM)
    message("platform ${PLATFORM}")
    if (PLATFORM STREQUAL "OS64" )
        add_compile_definitions(TORNADO_OS_IOS)
        set(OS_IOS 1)
        set(OS_NAME "ios")
    endif()
elseif (APPLE)
    add_compile_definitions(TORNADO_OS_MACOS)
    set(OS_MACOS 1)
    set(OS_NAME "macos")
elseif (UNIX)
    add_compile_definitions(TORNADO_OS_LINUX)
    set(OS_LINUX 1)
    set(OS_NAME "linux")

elseif (WIN32)
    add_compile_definitions(TORNADO_OS_WINDOWS)
    set(OS_WINDOWS 1)
    set(OS_NAME "windows")
endif()


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

if (OS_WINDOWS)
    target_compile_options(raff PRIVATE /F 5000000 /Wall /wd4668 /wd4820 /wd4100 /wd4710 /wd4711 /wd5945 /wd5105 /wd5045 /we4047 /we4255 /we4013) # /WX
else()
    # -Werror=missing-prototypes
    target_compile_options(raff PRIVATE -Wmost -Wall -Wextra -Wshadow -Wstrict-aliasing -ansi -pedantic -Wno-extra-semi-stmt -Wno-undef -Wno-unused-variable -Wno-unused-parameter -Wno-padded -Werror=implicit-function-declaration -Werror=incompatible-pointer-types  -Werror=missing-prototypes -Werror=int-conversion -Werror=return-type) # -Werror=incompatible-pointer-types-discards-qualifiers
    if (COMPILER_CLANG)
        target_compile_options(raff PRIVATE -Weverything -Werror=missing-variable-declarations)
    endif()
endif()

target_link_libraries(raff m)
