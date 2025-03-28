cmake_minimum_required(VERSION 3.30)
project(Grim C)

set(CMAKE_C_STANDARD 11)

# Specify the include directory
include_directories(include)

# Specify all source files
ADD_EXECUTABLE(Grim
        src/main.c
        src/ncurses_utils.c
        src/game_state.c
        src/card.c
        src/display.c
        src/input.c
)

# Link against ncurses
target_link_libraries(Grim -lncurses)