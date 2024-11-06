#include <iostream>
#include <fmt/chrono.h>
using Clock = std::chrono::high_resolution_clock;


#include <raylib.h>


#include <defines.hpp>

ivec2 screen_size(600, 400);
int main() 
{
    // Initialize window and framerate
    InitWindow(screen_size.x, screen_size.y, "Test Window");
    SetTargetFPS(60);

    // Keep track of time
    auto t = Clock::now();

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            auto now = Clock::now();
		    float elapsed_ms = static_cast<float>((std::chrono::duration_cast<std::chrono::microseconds>(now - t)).count()) / 1000.f;
		    t = now;
            DrawText("Test test test test", 20, 300, 40, BLACK);
            DrawText(("Time (ms) between frames: " + std::to_string(elapsed_ms)).c_str(), 20, 340, 20, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}