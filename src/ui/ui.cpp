#include <raylib.h>
#include "ui.hpp"

using namespace UI;

Font defaultFont = GetFontDefault();


Text::Text(ECS::Entity uiEntity, std::string content, int size, Font font): 
    content(std::move(content)),
    size(size), 
    font(font)
{
    ECS::registry<Text>.insert(uiEntity, *this, false);
}

void UISystem::step(float elapsed_ms, ivec2 screen_size)
{
    max_screen_size = screen_size;

    for(auto& entity : ECS::registry<Element<MENU>>.entities) {

    }
    for(auto& entity : ECS::registry<Element<DIALOGUE>>.entities) {
        
    }
    for(auto& entity : ECS::registry<Element<BUTTON>>.entities) {
        
    }
    return;
}
