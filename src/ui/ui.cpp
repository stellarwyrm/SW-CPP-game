#include <raylib.h>
#include "ui.hpp"

using namespace UI;

Font UI::defaultFont = GetFontDefault();


UI::Text::Text(ECS::Entity uiEntity, std::string content, int size, Font font): 
    content(std::move(content)),
    size(size), 
    font(font)
{
    ECS::registry<UI::Text>.insert(uiEntity, *this, false);
}