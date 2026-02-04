// kernel.c
#define VIDEO_MEMORY 0xB8000

void print_string(const char* str)
{
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    while (*str) {
        *video++ = *str++;
        *video++ = 0x07;
    }
}

void delay()
{
    volatile int i;
    for (i = 0; i < 1000000; i++);
}

void kernel_main(void)
{
    print_string("Hello, World!...");
    
    while (1)
        asm volatile ("hlt");
}