target_include_directories(${PROJECT_NAME} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/ecs
            ${CMAKE_CURRENT_SOURCE_DIR}/ui)

target_sources(${PROJECT_NAME} 
            PRIVATE
                ecs/ecs.hpp
                ui/ui.hpp
                common.hpp
                node.hpp
            PRIVATE
                ecs/ecs.cpp
                ui/ui.cpp
                node.cpp)


