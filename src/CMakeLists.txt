target_include_directories(${PROJECT_NAME} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/ecs
            ${CMAKE_CURRENT_SOURCE_DIR}/ui)

target_sources(${PROJECT_NAME} 
            PRIVATE
                ecs/ecs.hpp
                ui/ui.hpp
                defines.hpp
            PRIVATE
                ecs/ecs.cpp
                ui/ui.cpp)


