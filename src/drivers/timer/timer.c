#include "timer.h"
#include <stdint.h>

static uint32_t timer_ticks = 0;

void timer_init(void)
{
    uint16_t divisor = PIT_DIVISOR;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    __asm__ volatile("outb %%al, $0x43" : : "a"((uint8_t)0x36));
    
    __asm__ volatile("outb %%al, $0x40" : : "a"(low));
    
    __asm__ volatile("outb %%al, $0x40" : : "a"(high));
    
    timer_ticks = 0;
}

void timer_tick(void)
{
    timer_ticks++;
}

uint32_t timer_get_ticks(void)
{
    return timer_ticks;
}

void timer_wait(uint32_t milliseconds)
{
    uint32_t start_ticks = timer_get_ticks();
    uint32_t target_ticks = start_ticks + milliseconds;
    
    while (timer_get_ticks() < target_ticks)
    {
        __asm__ volatile("hlt");
    }
}
