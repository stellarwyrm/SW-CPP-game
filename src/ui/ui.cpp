#include <raylib.h>
#include "ui.hpp"


Font UI::defaultFont = GetFontDefault();

UI::Text::Text(ECS::Entity uiEntity, std::string content, int size, Font font): 
    content(std::move(content)),
    size(size), 
    font(font)
{
    ECS::registry<Text>.insert(uiEntity, *this);
}

UI::UISystem::UISystem()
{}

void UI::UISystem::drawTree(
    float elapsed_ms,  std::weak_ptr<UI::Transform> tree, 
    const ivec2& parent_size, const ivec2& relative_origin)
{
    if(tree.expired()) return;
    auto&& treeContent = tree.lock().get();
    // Draw root note
    // Calculate pixel size and coordinates
    auto size = treeContent->size;
    auto origin = treeContent->coords;


    // auto& e = treeContent->entity;
    drawTransform(size, origin, treeContent->entity);

    // Draw children nodes
    for(auto& child : treeContent->children) {
        drawTree(elapsed_ms, child, size, origin);
    }
    return;
}

void UI::UISystem::drawTransform(ivec2 size, ivec2 pixelPos, ECS::Entity& e)
{
    if(ECS::registry<Text>.has(e)) {
        auto t = ECS::registry<Text>.get(e);
        DrawText(t.content.c_str(), pixelPos.x, pixelPos.y, 20, BLUE);
    }
}

UI::Transform::Transform(ECS::Entity uiEntity, vec2 size, vec2 coords, bool isRelative):
    entity(std::move(uiEntity)),
    size(size),
    coords(coords),
    isRelative(isRelative)
{
}

void UI::Transform::clearAllChildren()
{
    // Delete children
    for(auto t : children) {
        auto child = t.get();
        if (child == nullptr) continue;
        child->clearAllChildren();
    }
    ECS::ContainerInterface::remove_all_components_of(entity);

    // Remove self from parent
    if(auto p = parent.lock()) {
        auto ptr = shared_from_this();
        p->removeChild(ptr);
    }
}


