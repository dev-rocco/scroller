cmake_minimum_required(VERSION 3.16)
project(C-Scroller)

set(CMAKE_C_STANDARD 11)

# Add include directories
include_directories(include)
include_directories(C:/Libraries/SDL2/include/SDL2)
include_directories(C:/Libraries/SDL2_ttf/include/SDL2)

set(SOURCES
    src/main.c
    src/renderer.c
    src/text_entity.c
    src/config.c
)

add_executable(banner ${SOURCES})

target_link_libraries(banner
    C:/Libraries/SDL2/lib/libSDL2.dll.a
    C:/Libraries/SDL2_ttf/lib/libSDL2_ttf.dll.a
)