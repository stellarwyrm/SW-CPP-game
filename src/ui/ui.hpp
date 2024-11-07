#pragma once
#include "raylib.h"
#include "defines.hpp"
#include "ecs.hpp"
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
     * @brief ScreenPosition is necessary for UI to be rendered. Indicates 
     * the screen coordinates or screen-relative coordinates of the element.
     * 
     */
    struct ScreenPosition {
        Vector2 coords;
        
    };

    /**
     * @brief Text block component.
     * 
     * An entity can have multiple of one.
     */
    struct Text {
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
        ivec2 screen_size;
    };
};



