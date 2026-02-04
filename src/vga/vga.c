#include "vga.h"

uint16_t* vga_buffer;
int vga_row;
int vga_column;

void vga_init()
{
    vga_buffer = (uint16_t*)VGA_BUFFER_ADDRESS;
    vga_row = 0;
    vga_column = 0;
}

uint8_t get_color_code(enum vga_color text_color, enum vga_color background_color)
{
    return text_color | (background_color << 4);
}

uint16_t get_char(char ch, uint8_t color)
{
    return (uint16_t) ch | ((uint16_t) color << 8);
}

void putchar(char ch, uint8_t color)
{
    if (vga_buffer == 0)
    {
        vga_buffer = (uint16_t*)VGA_BUFFER_ADDRESS;
    }
    
    switch (ch)
    {
        case '\n':
            vga_row++;
            vga_column = 0;
            break;
            
        case '\r':
            vga_column = 0;
            break;
            
        case '\t':
            do
            {
                vga_buffer[vga_row * VGA_BUFFER_WIDTH + vga_column] = get_char(' ', color);
                vga_column++;
            }
            while (vga_column % 8 != 0 && vga_column < VGA_BUFFER_WIDTH);
            break;
            
        case '\b':
            if (vga_column > 0)
            {
                vga_column--;
                vga_buffer[vga_row * VGA_BUFFER_WIDTH + vga_column] = get_char(' ', color);
            }
            break;
            
        case '\f':
            vga_row = 0;
            vga_column = 0;
            for (int i = 0; i < VGA_BUFFER_WIDTH * VGA_BUFFER_HEIGHT; i++)
                vga_buffer[i] = get_char(' ', color);
            break;
            
        case '\a':
            break;
            
        case '\v':
            vga_row++;
            break;
            
        default:
            if (ch >= 32 && ch <= 126)
            {
                vga_buffer[vga_row * VGA_BUFFER_WIDTH + vga_column] = get_char(ch, color);
                vga_column++;
            }
            break;
    }
    
    if (vga_column >= VGA_BUFFER_WIDTH)
    {
        vga_column = 0;
        vga_row++;
    }
    
    if (vga_row >= VGA_BUFFER_HEIGHT)
    {
        for (int y = 0; y < VGA_BUFFER_HEIGHT - 1; y++)
            for (int x = 0; x < VGA_BUFFER_WIDTH; x++)
                vga_buffer[y * VGA_BUFFER_WIDTH + x] = vga_buffer[(y + 1) * VGA_BUFFER_WIDTH + x];
        
        for (int x = 0; x < VGA_BUFFER_WIDTH; x++)
            vga_buffer[(VGA_BUFFER_HEIGHT - 1) * VGA_BUFFER_WIDTH + x] = get_char(' ', color);
        
        vga_row = VGA_BUFFER_HEIGHT - 1;
    }
}

void print(const char* text)
{
    for(int i = 0; text[i] != '\0'; i++)
        putchar(text[i], get_color_code(DEFAULT_VGA_TEXT_COLOR, DEFAULT_VGA_BACKGROUND_COLOR));
}