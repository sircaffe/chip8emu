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

// sample sprites


Sprite smile = {
    .row = {0x42, 0xA5, 0x00, 0x3C, 0x18}
};

Sprite text[4] = {
    {
        .row = {0x80, 0xF0, 0x80, 0x80, 0x70}
    },
    {
        .row = {0xE0, 0x90, 0xF0, 0x80, 0x70}
    },
    {
        .row = {0x70, 0x80, 0x60, 0x10, 0xE0}
    },
    {
        .row = {0x80, 0xF0, 0x80, 0x80, 0x70}
    }
};

// 0100 0010
// 1010 0101
// 0000 0000
// 0011 1100
// 0001 1000

void draw_sprite(size_t x, size_t y, Sprite sprite) {
    for (int dy = 0; dy <= 4; ++dy) {
        for (int dx = 7; dx >= 0; --dx) {
            if ((sprite.row[dy] << dx) & 0x80) draw_pixel(dx+x, dy+y);
        }
    }
}

void update_screen() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int col = 0; col < WIDTH; ++col) {
            int x = col % WIDTH;

            if (screen[y*WIDTH+x] == true) {
                DrawRectangle(x*PIXEL_SIZE, y*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, BLACK);
            }
        }
    }
}

int main(void)
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(WIDTH*PIXEL_SIZE, HEIGHT*PIXEL_SIZE, "CHIP-8 Emulator");

    memset(screen, false, WIDTH*HEIGHT);
    
    // --- Hardcoded sample text rendering
    int offset = 16;
    int spacing = 5;

    for (int i = 0; i < 5; ++i) {
        draw_sprite(i*spacing+offset, (HEIGHT/2) - 2, text[i]);
    }
    draw_sprite(4*spacing+offset, (HEIGHT/2) - 2, smile);
    // --- Hardcoded sample text rendering

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            update_screen();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
