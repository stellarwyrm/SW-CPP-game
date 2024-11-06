cmake_minimum_required(VERSION 3.20)
project(sw-cpp VERSION 0.1.0 
                DESCRIPTION "stellarwyrm's CPP Game Engine"
                LANGUAGES C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows
    set(IS_WINDOWS 1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux
    set(IS_LINUX 1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS
    set(IS_MACOS 1)
else()
    message(FATAL_ERROR "OS not supported.")
endif()

# Executable 
add_executable(${PROJECT_NAME} 
                src/main.cpp)
target_compile_features(${PROJECT_NAME} 
                PUBLIC
                cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS 0)

# Dependencies
find_library(RAY_LIB raylib ext/raylib/libraylib.a)
find_path(RAYLIB_INCLUDES raylib.h ext/raylib/raylib.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${RAYLIB_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${RAY_LIB})

if (IS_MACOS)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# CMake options
option(DEBUG_MODE "Enable debug mode." OFF)




