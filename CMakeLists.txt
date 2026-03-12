cmake_minimum_required(VERSION 3.16)

project(MenuProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/Auth.cpp
    src/Creds.cpp
    src/Database.cpp
    src/Security.cpp
    src/term/term.cpp

    src/menu/core/menu.cpp
    src/menu/core/menu_render.cpp
    src/menu/core/menu_render_primary.cpp
    src/menu/core/menu_render_secondary.cpp

    src/menu/main/main_menu.cpp
    src/menu/main/menu_render_main.cpp

    src/menu/number/number_menu.cpp
    src/menu/number/menu_render_number.cpp

    src/menu/options/option_menu.cpp
    src/menu/options/menu_render_options.cpp

    src/menu/text/text_menu.cpp
    src/menu/text/menu_render_text.cpp
)

add_executable(klip ${SOURCES})

# Incluir directorios de headers
target_include_directories(menu_app PRIVATE
    src
    src/menu
    src/menu/core
    src/menu/main
    src/menu/number
    src/menu/options
    src/menu/text
    src/term
)
