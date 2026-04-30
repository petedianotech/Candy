cmake_minimum_required(VERSION 3.22)
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
    src/main.cpp
    src/game.cpp
    src/board.cpp
    src/tile.cpp
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