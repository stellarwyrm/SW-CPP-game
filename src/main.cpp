#include <iostream>
#include <raylib.h>

int main() 
{
    // Initialize window and framerate
    InitWindow(600, 400, "Test Window");
    SetTargetFPS(60);


    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            
            DrawText("Test test test test", 50, 300, 40, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}