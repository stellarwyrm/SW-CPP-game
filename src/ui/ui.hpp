#pragma once
#include "raylib.h"
#include "common.hpp"
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
     * @brief ScreenPos is necessary for UI to be rendered. Indicates 
     * the screen coordinates or screen-relative coordinates of the element.
     * 
     */
    struct ScreenPos {
        Vector2 coords;
        bool isScreenRelative;
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



