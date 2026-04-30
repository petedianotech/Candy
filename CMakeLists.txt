cmake_minimum_required(VERSION 3.22)
<<<<<<< HEAD
project(FruitBurst CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Try to find graphics libraries
find_package(raylib CONFIG QUIET)
find_package(SDL2 CONFIG QUIET)

# Main executable
add_executable(FruitBurst
=======
project(FruitBurst)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Android specific settings
if(ANDROID)
    set(CMAKE_SYSTEM_NAME Android)
    set(CMAKE_SYSTEM_VERSION 21) # Minimum API level
    set(CMAKE_ANDROID_ARCH_ABI arm64-v8a) # Or armeabi-v7a for 32-bit
    set(CMAKE_ANDROID_NDK $ENV{ANDROID_NDK_ROOT})
    set(CMAKE_ANDROID_STL_TYPE c++_static)
endif()

# Fetch Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.5.0.zip
)
FetchContent_MakeAvailable(raylib)

# Include directories
include_directories(include)

# Source files
set(SOURCES
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
    src/main.cpp
    src/game.cpp
    src/board.cpp
    src/tile.cpp
<<<<<<< HEAD
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


=======
    src/ui.cpp
    src/input_handler.cpp
    src/particle_system.cpp
    src/sound_manager.cpp
)

# Header files
set(HEADERS
    include/game.h
    include/board.h
    include/tile.h
    include/ui.h
    include/input_handler.h
    include/particle_system.h
    include/sound_manager.h
    include/config.h
)

# Create executable
if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME} raylib)

# Android specific
if(ANDROID)
    # Link Android libraries
    target_link_libraries(${PROJECT_NAME} android log EGL GLESv2 OpenSLES atomic)

    # Set properties for Android APK
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}
    )
endif()

# Copy assets (if any)
# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
