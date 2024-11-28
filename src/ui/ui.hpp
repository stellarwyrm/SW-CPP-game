#pragma once
#include "raylib.h"
#include "common.hpp"
#include "ecs.hpp"
#include "node.hpp"
#include "graphic.hpp"
#include "interactible.hpp"
#include <string>
#include <map>

namespace UI {

    enum Tag {
        NONE,
        MENU,
        DIALOGUE,
        BUTTON
    };

    struct Style {

    };

    /**
     * @brief UI:Element component
     * 
     * All UI entities must have this component. Element also indicates the
     * tag of the element.
     * 
     */
    struct Element : virtual Component {
        static ECS::Entity createUI() {
            auto e = ECS::Entity();
            ECS::registry<Element>.emplace(e);
            return e;
        }
        static bool isActive(ECS::Entity e) {
            return 
                ECS::registry<Element>.has(e) &&
                ECS::registry<Element>.get(e).active;
        }
        bool active = true;
        Tag tag;
    };

    /**
     * @brief Transform is the (n-ary tree) entity class for UI. Indicates 
     * the screen coordinates or screen-relative coordinates of the element.
     * Also indicates size, rotation, etc.
     *  
     * Coordinates start from the top left. 
     */
    struct Transform : virtual TreeNode<Transform> {
        static std::shared_ptr<Transform> createTransform(
            vec2 size = vec2(0,0), 
            vec2 coords = vec2(0,0), 
            bool isRelative = false);
        Transform(ECS::Entity uiEntity, vec2 size, vec2 coords, bool isRelative);
        vec2 size;
        vec2 coords;
        ECS::Entity entity;
        /**
         * @brief If isRelative is true, size and coords relative to parent. 
         * If there is no parent component, then isRelative is treated as
         * false.
         * For example, for isRelative == true, then a size of {1,1} would mean
         * that the item is the same size as its parent.
         */
        bool isRelative;
        void clearAllChildren();
        void draw();
        ECS::Entity& addChild(std::shared_ptr<Transform> child) {
            children.push_back(child);
            child->parent = this->weak_from_this();
            return child->entity;
        }
    };


    /**
     * @brief UISystem, running on all UI::Elements. 
     * 
     */
    class UISystem {
    public:
        UISystem();
        ivec2 max_screen_size = ivec2(0,0);
        /**
         * @brief Incremental step for UISystem
         * 
         * @param elapsed_ms Since last step.
         * @param screen_size 
         */
        // void step(float elapsed_ms, const ivec2& screen_size);

        void drawTree(float elapsed_ms,  std::weak_ptr<UI::Transform> tree, 
            const ivec2& parent_size, const ivec2& relative_origin = ivec2(0,0));

        
    private:
        void arrangeTree(
                float elapsed_ms,  std::weak_ptr<UI::Transform> tree, 
                const ivec2& parent_size, const ivec2& relative_origin);
        void arrangeTransform(ivec2 size, ivec2 pixelPos, ECS::Entity& e);
        void drawTransform(ECS::Entity e);
        std::multimap<int, ECS::Entity> drawList;
    };
};



