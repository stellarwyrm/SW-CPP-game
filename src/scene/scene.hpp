#pragma once

#include "node.hpp"
#include "ui.hpp"
#include <nlohmann/json.hpp>


// TODO:
// Scenes mostly loaded from json?
// Maybe scene editor is built in, and if there are
// no valid scenes, then default to scene editor.

/**
 * @brief Contains information about scene and sub-scenes.
 * Sub-scenes are useful for things such as a menu tree. 
 */
struct Scene {
    std::string name;
};

static Scene SceneEditor;

class SceneSystem {
    void step(float elapsed_ms, ivec2 screen_size);
};