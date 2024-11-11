#include "scene.hpp"

Scene::Scene(std::string name, vec2 screen_size): 
    name(std::move(name)),
    screen(std::shared_ptr<UI::Transform>(
        new UI::Transform(UI::Element::createUI(), vec2(screen_size.x, screen_size.y),vec2(0,0),false))) 
{
    std::hash<std::string> hash;
    sceneID = hash(name);
}

SceneSystem::SceneSystem(ivec2 screen_size)
{
    // currentScene = &sceneEditor;
    if(scenes.nodes.empty()) {
        auto&& s = sceneEditor();
        currentScene = s;
        scenes.addNode(std::move(s));
    }
}

void SceneSystem::loadScene(const Scene scene)
{
    if(scene.sceneID != currentScene->sceneID) {
        unloadCurrentScene();
        // currentScene = &scene;
    }
}

std::shared_ptr<Scene> SceneSystem::sceneEditor() {
    auto scene = new Scene("Scene Editor", vec2(0, 0));
    auto&& screen = scene->screen;

    auto& e = screen->entity;
    UI::Text(e, "the scene editor");

    return std::shared_ptr<Scene>(scene);
}

void SceneSystem::unloadCurrentScene() 
{
    currentScene->screen->clearAllChildren();
}

void SceneSystem::step(float elapsed_ms, const ivec2& screen_size)
{
    ui.drawTree(elapsed_ms, currentScene->screen, screen_size);
}

SceneSystem::~SceneSystem()
{
    // for 
}
