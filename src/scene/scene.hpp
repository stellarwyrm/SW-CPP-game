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
struct Scene : public GraphNode<Scene> {
    Scene() = delete;
    Scene(std::string name, vec2 screen_size);
    std::string name;
    unsigned int sceneID;
    std::shared_ptr<UI::Transform> screen;
};

struct SceneTransition : public GraphEdge<Scene> {
};

struct SceneGraph : public Graph<Scene, SceneTransition> {
};

class SceneSystem {
    public:
        SceneSystem(ivec2 screen_size);
        void loadScene(const Scene scene);
        void loadSceneTransition(const SceneTransition nextScene);
        void unloadCurrentScene();
        void step(float elapsed_ms, const ivec2& screen_size);
        ~SceneSystem();
    private: 
        SceneGraph scenes;
        std::shared_ptr<Scene> currentScene;
        UI::UISystem ui;
        static std::shared_ptr<Scene> sceneEditor();
};