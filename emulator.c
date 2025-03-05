#include <string.h>

#include "./lib/raylib.h"

#define WIDTH 64
#define HEIGHT 32

#define PIXEL_SIZE 8

bool screen[WIDTH*HEIGHT];

int main(void)
{
    InitWindow(WIDTH*PIXEL_SIZE, HEIGHT*PIXEL_SIZE, "CHIP-8 Emulator");

    memset(screen, false, WIDTH*HEIGHT);

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int row = 0; row < HEIGHT; ++row) {
                for (int col = 0; col < WIDTH; ++col) {
                    int x = col % WIDTH;
                    
                    if (screen[row*WIDTH+x] == true) {
                        DrawRectangle(x*PIXEL_SIZE, row*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, BLACK);
                    }
                }
            }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
