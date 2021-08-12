cmake_minimum_required(VERSION 3.20)
project(dizzy)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        /usr/local/include
)

link_directories(/usr/local/lib)

file(GLOB SRCS_G
        src/*.cpp
        )

add_executable(dizzy ${SRCS_G})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_mixer mpg123 pthread ao fftw3)