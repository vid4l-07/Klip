cmake_minimum_required(VERSION 3.16)

project(Klip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/Database.cpp
    src/Security.cpp
    src/RecentDatabases.cpp

    src/term/term.cpp

    src/menu/core/menu.cpp
    src/menu/core/menu_render.cpp

    src/menu/main/main_menu.cpp

    src/menu/db/db_menu.cpp
    src/menu/db/menu_render_db.cpp

    src/menu/number/number_menu.cpp
    src/menu/number/menu_render_number.cpp

    src/menu/options/option_menu.cpp
    src/menu/options/menu_render_options.cpp

    src/menu/text/text_menu.cpp
    src/menu/text/menu_render_text.cpp

    src/menu/path/path_menu.cpp
)

add_executable(klip ${SOURCES})

# Includes
target_include_directories(klip PRIVATE
    src
    src/menu
    src/menu/core
    src/menu/main
    src/menu/number
    src/menu/options
    src/menu/text
    src/term

    # libsodium headers
    src/lib
)

# Link con libsodium.a
target_link_libraries(klip PRIVATE
    ${CMAKE_SOURCE_DIR}/src/lib/libsodium.a
)
