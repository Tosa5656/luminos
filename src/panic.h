#include "vga/vga.h"

void panic(const char* text)
{
    clear_screen(get_color_code(VGA_COLOR_WHITE, VGA_COLOR_BLUE));

    vga_row = VGA_BUFFER_HEIGHT / 2 - 2;
    print_centered("Error! Kernel panic!", get_color_code(VGA_COLOR_WHITE, VGA_COLOR_BLUE));

    vga_row = VGA_BUFFER_HEIGHT / 2;
    print_centered(text, get_color_code(VGA_COLOR_WHITE, VGA_COLOR_BLUE));
}