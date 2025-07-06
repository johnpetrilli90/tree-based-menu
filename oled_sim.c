#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "menu.h"
#include "oled_sim.h"

#define WIDTH 96
#define HEIGHT 32

static uint8_t framebuffer[HEIGHT][WIDTH];

void oled_clear() {
    memset(framebuffer, 0, sizeof(framebuffer));
}

void oled_draw_text(int x, int y, const char* text) {
    // Simulate drawing by setting pixels (we just draw a line of text indicator)
    for (int i = 0; text[i] && x + i < WIDTH; i++) {
        for (int j = 0; j < 6 && y + j < HEIGHT; j++) {
            framebuffer[y + j][x + i] = 255;  // Simulate white pixel
        }
    }
}

void oled_render_menu(MenuNode* node) {
    oled_clear();
    int start_y = 0;

    for (int i = 0; i < node->child_count && i < 4; i++) {
        char line[64];
        snprintf(line, sizeof(line), "%c %s", (i == node->selected_index) ? '>' : ' ', node->children[i]->name);
        oled_draw_text(0, start_y, line);
        start_y += 8;
    }

    oled_save_to_bmp("oled.bmp");
}

void oled_save_to_bmp(const char* filename) {
    FILE* f;
    int filesize = 54 + WIDTH * HEIGHT;
    uint8_t bmpfileheader[14] = {
        'B','M', filesize, 0, 0, 0, 0,0, 0,0, 54,0,0,0
    };
    uint8_t bmpinfoheader[40] = {
        40,0,0,0, WIDTH,0,0,0, HEIGHT,0,0,0,
        1,0,8,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
        0,0,0,0
    };

    bmpfileheader[ 2] = (uint8_t)(filesize);
    bmpfileheader[ 3] = (uint8_t)(filesize >> 8);
    bmpfileheader[ 4] = (uint8_t)(filesize >> 16);
    bmpfileheader[ 5] = (uint8_t)(filesize >> 24);
    bmpinfoheader[ 4] = WIDTH;
    bmpinfoheader[ 5] = 0;
    bmpinfoheader[ 8] = HEIGHT;
    bmpinfoheader[ 9] = 0;

    f = fopen(filename,"wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);

    for(int y = HEIGHT - 1; y >= 0; y--) {
        for(int x = 0; x < WIDTH; x++) {
            uint8_t p = framebuffer[y][x];
            fwrite(&p, 1, 1, f);
        }
    }
    fclose(f);
}
