#pragma once

#include <raylib.h>
#include <common.hpp>

namespace UI {
    struct BackgroundStyle {
        BackgroundStyle(rgba flat_color);
        BackgroundStyle(rgba gradient1, rgba gradient2, bool isHorizontal);
        Image background;
    };

    struct Box {
    };
};