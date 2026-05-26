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

    src/ui/core/menu.cpp
    src/ui/core/menu_render.cpp

    src/ui/main/main_menu.cpp
    src/ui/main/main_menu_render.cpp

    src/ui/db/db_menu.cpp
    src/ui/db/menu_render_db.cpp
    src/ui/db/workflows/new_pass_workflow.cpp

    src/ui/number/number_menu.cpp
    src/ui/number/menu_render_number.cpp

    src/ui/options/option_menu.cpp
    src/ui/options/menu_render_options.cpp

    src/ui/text/text_menu.cpp
    src/ui/text/menu_render_text.cpp

	src/ui/message/message.cpp
    src/ui/path/path_menu.cpp
    src/ui/help/help.cpp
)

add_executable(klip ${SOURCES})

# Includes
target_include_directories(klip PRIVATE
    src

	# Libraries
	src/lib
)

# Link con libsodium.a
target_link_libraries(klip PRIVATE
    ${CMAKE_SOURCE_DIR}/src/lib/libsodium.a
)
