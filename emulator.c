#include <stdint.h>
#include <string.h>

#include "./lib/raylib.h"

#define WIDTH 64
#define HEIGHT 32

#define PIXEL_SIZE 8

bool screen[WIDTH*HEIGHT];

typedef struct {
    uint8_t PC;

    uint16_t I;
    uint8_t VX[15];
    
    uint8_t RAM[4095];
    uint16_t STACK[15];
    uint8_t SP;
    
    uint8_t delay_timer;
    uint8_t sound_timer;
    
} Chip8;

// sprites are 8x5 pixels sized
typedef struct {
    uint8_t row[5];
} Sprite;

void draw_pixel(size_t x, size_t y) {
    if (x < WIDTH && y < HEIGHT) screen[y*WIDTH+x] = true;
}

void draw_sprite(size_t x, size_t y, Sprite sprite) {
    // TODO: decode each bit from Sprite rows and render
}

int main(void)
{
    InitWindow(WIDTH*PIXEL_SIZE, HEIGHT*PIXEL_SIZE, "CHIP-8 Emulator");

    memset(screen, false, WIDTH*HEIGHT);
    draw_pixel(63, 31);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int y = 0; y < HEIGHT; ++y) {
                for (int col = 0; col < WIDTH; ++col) {
                    int x = col % WIDTH;
                    
                    if (screen[y*WIDTH+x] == true) {
                        DrawRectangle(x*PIXEL_SIZE, y*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, BLACK);
                    }
                }
            }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
