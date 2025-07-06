#pragma once
#include "menu.h"

void oled_clear();
void oled_draw_text(int x, int y, const char* text);
void oled_render_menu(MenuNode* node);
void oled_save_to_bmp(const char* filename);
