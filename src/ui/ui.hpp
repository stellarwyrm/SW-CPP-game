#pragma once
#include "raylib.h"
#include "common.hpp"
#include "ecs.hpp"
#include "node.hpp"
#include <string>

namespace UI {

    extern Font defaultFont;

    enum Tag {
        MENU,
        DIALOGUE,
        BUTTON
    };
    /**
     * @brief UI:Element component
     * 
     * All UI entities must have this component. Element also indicates the
     * tag of the element.
     * 
     */
    template <Tag T> struct Element {
        static ECS::Entity createUI() {
            auto e = ECS::Entity();
            ECS::registry<Element<T>>.emplace(e);
            return e;
        }
        bool active = true;
    };

    /**
     * @brief Transform is necessary for UI to be rendered. Indicates 
     * the screen coordinates or screen-relative coordinates of the element.
     * Also indicates size, rotation, etc.
     *  
     * Coordinates start from the top left. 
     */
    struct Transform : NodeComponent {
        Vector2 size;
        Vector2 coords;
        /**
         * @brief If isRelative is true, size and coords relative to parent. 
         * If there is no parent component, then isRelative is treated as
         * false.
         * For example, for isRelative == true, then a size of {1,1} would mean
         * that the item is the same size as its parent.
         */
        bool isRelative;
    };

    /**
     * @brief Text block component.
     * 
     * An entity can have multiple of one.
     */
    struct Text {
        /**
         * @brief Add text component to an entity.
         * 
         * @param uiEntity The entity to which the text component will be added to
         * @param content 
         * @param size Font size
         * @param font If none given, value set to defaultFont
         */
        Text(ECS::Entity uiEntity, std::string content, int size = 20, Font font = defaultFont);
        std::string content;
        Font font;
        int size;
    };

    /**
     * @brief UISystem, running on all UI::Elements. 
     * 
     */
    class UISystem {
        ivec2 max_screen_size;
        /**
         * @brief Incremental step for UISystem
         * 
         * @param elapsed_ms Since last step.
         * @param screen_size 
         */
        void step(float elapsed_ms, ivec2 screen_size);
    };
};



