#include <iostream>
#include <fmt/chrono.h>
using Clock = std::chrono::high_resolution_clock;


#include <raylib.h>


#include "common.hpp"
#include "node.hpp"


#include "ui.hpp"
#include "ecs.hpp"
#include "scene.hpp"

ivec2 screen_size(600, 400);
int main() 
{
    // Initialize window and framerate
    InitWindow(screen_size.x, screen_size.y, "Test Window");
    SetTargetFPS(60);

    // try
    // {
    //     auto g = Graph();
    //     auto nodeA = GraphNode::createNode();
    //     auto nodeB = GraphNode::createNode();
    //     auto edge = nodeA->attachNode(nodeB);

    //     g.addNode(nodeA);
    //     g.addNode(nodeB);
    //     g.addEdge(edge);
    // }
    // catch (const std::bad_weak_ptr& e)
    // {
    //     std::cout << e.what() << '\n';
    // }

    // Keep track of time
    auto t = Clock::now();

    // UI::UISystem ui = UI::UISystem(); 
    SceneSystem scene = SceneSystem(screen_size); 

    unsigned int flags = FLAG_WINDOW_RESIZABLE;
    SetWindowState(flags);


    while(!WindowShouldClose()) {
        auto now = Clock::now();
        float elapsed_ms = static_cast<float>((std::chrono::duration_cast<std::chrono::microseconds>(now - t)).count()) / 1000.f;
        t = now;

        if(IsWindowResized()) {
            screen_size.x = GetScreenWidth();
            screen_size.y = GetScreenHeight();
        }
        scene.step(elapsed_ms, screen_size);

        BeginDrawing();
        
        ClearBackground(LIGHTGRAY);
        DrawText("Test test test test", 0, 0, 40, BLACK);
        DrawText(("Time (ms) between frames: " + std::to_string(elapsed_ms)).c_str(), 20, screen_size.y - 60, 20, RED);



        EndDrawing();
    }

    CloseWindow();


    return 0;
}

void Draw() {

}