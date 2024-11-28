#include "graphic.hpp"

Font UI::defaultFont = GetFontDefault();

UI::FlatBG::FlatBG(rgba flat_color)
{
    color = flat_color;
}

Image UI::FlatBG::renderBG(vec2 size) {
    return GenImageColor(size.x, size.y, color);
}

UI::Box::Box(BackgroundStyle bg) :
    bg(bg)
{
    tex = UI::Tex();
}

void UI::Box::redraw(ivec2 size, ivec2 pixelPos)
{
    tex.redraw(LoadTextureFromImage(bg->renderBG(size)), pixelPos);
}

// UI::Box::~Box()
// {
//     bg.reset();
// }

Image UI::GradientBG::renderBG(vec2 size)
{
    return Image();
}

void UI::Tex::redraw(Texture2D tex, ivec2 pixelPos)
{
    this->tex = tex;
    loaded = true;
    this->pixelPos = pixelPos;
}

void UI::Tex::draw()
{
    DrawTexture(tex, pixelPos.x, pixelPos.y, tint);
}

UI::Text::Text(ECS::Entity uiEntity, std::string content, int size, rgba color, Font font): 
    content(std::move(content)),
    size(size), 
    color(color),
    font(font)
{
    ECS::registry<Text>.insert(uiEntity, *this);
}

void UI::Text::draw() {
    DrawText(content.c_str(), pixelPos.x, pixelPos.y, 20, color);
}