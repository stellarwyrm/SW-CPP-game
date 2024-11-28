#pragma once

#include <raylib.h>
#include <common.hpp>
#include <ecs.hpp>

namespace UI {
    class BG {
    public:
        BG() {};
        virtual Image renderBG(vec2 size) = 0;
        ~BG() = default;
    protected:
        int i;
    };

    class FlatBG : public BG {
    public:
        FlatBG(rgba flat_color);
        Image renderBG(vec2 size) override;
        rgba color;
    };

    class GradientBG : public BG {
        public:
        rgba gradient1;
        rgba gradient2;
        bool isHorizontal;
        GradientBG(rgba gradient1, rgba gradient2, bool isHorizontal) : BG(),
            gradient1(gradient1), gradient2(gradient2), isHorizontal(isHorizontal) {}
        Image renderBG(vec2 size) override;
    };
    typedef std::shared_ptr<BG> BackgroundStyle;

    // TODO: replace this with a layers thing instead
    struct Tex {
        Tex(){
            loaded = false;
        }
        Tex(Texture2D tex): tex(tex) {
            loaded = false;
        }
        bool isLoaded() {
            return loaded;
        }
        Texture2D getTex() {
            return tex;
        }
        /**
         * @brief Called whenever a component's texture is changed
         * 
         * @param tex 
         * @param pixelPos
         */
        void redraw(Texture2D tex, ivec2 pixelPos);
        void draw();
    private:
        ivec2 pixelPos{0,0};
        rgba tint = WHITE;
        bool loaded;
        Texture2D tex;
    };

    struct Box {
        Tex tex;
        BackgroundStyle bg;
        Box(BackgroundStyle bg);
        void redraw(ivec2 size, ivec2 pixelPos);
        // ~Box();
    };

    extern Font defaultFont;

    /**
     * @brief Text block component.
     * 
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
        Text(ECS::Entity uiEntity, std::string content, int size = 20, rgba color = BLACK, Font font = defaultFont);
        std::string content;
        rgba color;
        Font font;
        int size;
        ivec2 pixelPos{0,0};
        void draw();
    };
};