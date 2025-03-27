#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "raylib.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

#define PIXEL_SIZE 8

bool screen[SCREEN_WIDTH*SCREEN_HEIGHT];

typedef struct {
    uint16_t PC;

    uint16_t I;
    uint8_t VN[15]; // VF (V[15]) is flag register
    
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
    if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT) screen[y*SCREEN_WIDTH+x] = true;
}

void draw_sprite(size_t x, size_t y, Sprite sprite) {
    for (int dy = 0; dy <= 4; ++dy) {
        for (int dx = 7; dx >= 0; --dx) {
            if ((sprite.row[dy] << dx) & 0x80) draw_pixel(dx+x, dy+y);
        }
    }
}

void update_screen() {
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int col = 0; col < SCREEN_WIDTH; ++col) {
            int x = col % SCREEN_WIDTH;

            if (screen[y*SCREEN_WIDTH+x] == true) {
                DrawRectangle(x*PIXEL_SIZE, y*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, BLACK);
            }
        }
    }
}

int load_rom_into_ram(Chip8 *chip8, char *path_to_rom) {
    FILE *f = fopen(path_to_rom, "rb");
    if (f == NULL) {
        fprintf(stderr, "ERROR: could not read rom %s\n", path_to_rom);
        return 1;
    }
    
    fseek(f, 1, SEEK_END);
    size_t rom_size = ftell(f);
    rewind(f);

    char *buff = malloc(sizeof(char)*rom_size);
    memset(buff, 0, rom_size);
    
    for (int i = 0; i < rom_size; ++i) {
        fread(buff, 1, rom_size, f);
    }
    memcpy(chip8->RAM, buff, rom_size);
    fclose(f);
    return 0;
}

int main(void) {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(SCREEN_WIDTH*PIXEL_SIZE, SCREEN_HEIGHT*PIXEL_SIZE, "CHIP-8 Emulator");

    memset(screen, false, SCREEN_WIDTH*SCREEN_HEIGHT);

    Chip8 chip8 = {0};

    // TODO: Unhardcode loading roms
    load_rom_into_ram(&chip8, "./roms/chip8-roms/programs/IBM Logo.ch8");
    
    for (size_t i = 0; i < 10; ++i) {
        printf("0x%x, \n", chip8.RAM[i]);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            update_screen();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
