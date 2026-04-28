cmake_minimum_required(VERSION 3.22)
project(FruitBurst CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Try to find graphics libraries
find_package(raylib CONFIG QUIET)
find_package(SDL2 CONFIG QUIET)

# Main executable
add_executable(FruitBurst
    src/main.cpp
    src/game.cpp
    src/board.cpp
    src/tile.cpp
    src/input_handler.cpp
    src/particle_system.cpp
    src/ui.cpp
    src/sound_manager.cpp
)

target_include_directories(FruitBurst PRIVATE include)

# Link with graphics library if available, otherwise build headless
if(raylib_FOUND)
    message(STATUS "Found Raylib - building with full graphics support")
    target_link_libraries(FruitBurst PRIVATE raylib)
    target_compile_definitions(FruitBurst PRIVATE USE_RAYLIB=1)
elseif(SDL2_FOUND)
    message(STATUS "Found SDL2 - building with SDL2 graphics support")
    target_link_libraries(FruitBurst PRIVATE SDL2::SDL2)
    target_compile_definitions(FruitBurst PRIVATE USE_SDL2=1)
else()
    message(STATUS "No graphics library found - building headless/demo mode")
    target_compile_definitions(FruitBurst PRIVATE HEADLESS_MODE=1)
endif()

# Optional: Copy assets if they exist
if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    add_custom_command(TARGET FruitBurst POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
        COMMENT "Copying asset files"
    )
endif()

# Installation configuration
install(TARGETS FruitBurst DESTINATION bin)


