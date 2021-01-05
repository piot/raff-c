cmake_minimum_required(VERSION 3.17)
project(raff_example C)

set(CMAKE_C_STANDARD 99)

set(deps ../deps/)

add_executable(raff_example
    main.c
    )

target_compile_options(raff_example PRIVATE -Wall -Wno-unused-variable)

target_link_libraries(raff_example raff m)