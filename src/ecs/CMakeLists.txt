# main executable
add_library(ecs INTERFACE)
target_sources(${PROJECT_NAME} PRIVATE
                ecs.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
                ecs.hpp)
