#include <raylib.h>
#include "ui.hpp"
#include "graphic.hpp"



UI::UISystem::UISystem()
{}

void UI::UISystem::drawTree(
    float elapsed_ms, std::weak_ptr<UI::Transform> tree, 
    const ivec2 &parent_size, const ivec2 &relative_origin)
{
    arrangeTree(elapsed_ms, tree, parent_size, relative_origin);
    for (auto const& [layer_order, e]:drawList) {
        drawTransform(e);
    }
}

void UI::UISystem::arrangeTree(
    float elapsed_ms, std::weak_ptr<UI::Transform> tree,
    const ivec2 &parent_size, const ivec2 &relative_origin)
{
    if(tree.expired()) return;
    auto&& treeContent = tree.lock().get();
    // Draw root note
    // Calculate pixel size and coordinates
    auto size = treeContent->size;
    auto origin = treeContent->coords;

    if (treeContent->isRelative) {
        size = vec2(parent_size) * size;
        origin = vec2(relative_origin) + vec2(parent_size) * origin;
    }

    // Draw children nodes first
    for(auto& child : treeContent->children) {
        arrangeTree(elapsed_ms, child, size, origin);
    }

    if (UI::Element::isActive(treeContent->entity)) { 
        arrangeTransform(size, origin, treeContent->entity);
        drawList.insert({0, treeContent->entity});
    }
    return;
}

void UI::UISystem::arrangeTransform(ivec2 size, ivec2 pixelPos, ECS::Entity& e)
{
    if(ECS::registry<Box>.has(e)) {
        auto& b = ECS::registry<Box>.get(e);
        if (!b.tex.isLoaded()) {
            b.redraw(size, pixelPos);
        }
    }
    if(ECS::registry<Text>.has(e)) {
        auto& t = ECS::registry<Text>.get(e);
        t.pixelPos = pixelPos;
    }
}

void UI::UISystem::drawTransform(ECS::Entity e)
{
    if (!ECS::registry<Transform>.has(e)) return;
    auto t = ECS::registry<Transform>.get(e);
    if(ECS::registry<Box>.has(e)) {
        auto& b = ECS::registry<Box>.get(e);
        b.tex.draw();
    }
    if(ECS::registry<Text>.has(e)) {
        auto& t = ECS::registry<Text>.get(e);
        t.draw();
    }
}

std::shared_ptr<UI::Transform> UI::Transform::createTransform(vec2 size, vec2 coords, bool isRelative)
{
    auto s = std::shared_ptr<UI::Transform>(
        new UI::Transform(UI::Element::createUI(), size, coords, isRelative));
    return s;
}

UI::Transform::Transform(ECS::Entity uiEntity, vec2 size, vec2 coords, bool isRelative)
 :  entity(uiEntity),
    size(size),
    coords(coords),
    isRelative(isRelative)
{
    ECS::registry<Transform>.emplace(entity, *this);
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


