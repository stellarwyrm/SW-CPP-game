target_include_directories(${PROJECT_NAME} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/ecs
            ${CMAKE_CURRENT_SOURCE_DIR}/ui
            ${CMAKE_CURRENT_SOURCE_DIR}/scene)

add_subdirectory(ecs)
add_subdirectory(ui)
add_subdirectory(scene)

# target_sources(${PROJECT_NAME} 
#             PRIVATE
#                 ecs/ecs.hpp
#                 ui/ui.hpp
#                 common.hpp
#                 node.hpp
#             PRIVATE
#                 ecs/ecs.cpp
#                 ui/ui.cpp
#                 node.cpp)


