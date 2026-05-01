cmake_minimum_required(VERSION 3.22)
project(FruitBurst)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Create library for Android
if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
    
    # Link Android libraries
    target_link_libraries(${PROJECT_NAME} 
        android 
        log 
        EGL 
        GLESv2 
        OpenSLES 
        atomic
    )
    
    # Set properties for Android APK
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}
    )
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
endif()