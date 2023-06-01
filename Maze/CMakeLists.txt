cmake_minimum_required(VERSION 3.23)
project(Maze C)

set(CMAKE_C_STANDARD 99)

#add all files in libgraphics both .h and .c
file(GLOB libgraphics
        "libgraphics/*.h"
        "libgraphics/*.c"

        )
#add all files in the project's directory,like menu.c


add_executable(Maze main.c block.c file.c menu.c randomGeneration.c solution.h solution.c macro_and_system.h)
#why undefined reference to `SetWindowTitle'?
target_link_libraries(Maze ${libgraphics})