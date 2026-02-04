#include <stdint.h>

#define PIT_FREQUENCY 1000
#define PIT_DIVISOR 1193

void timer_init(void);
void timer_tick(void);
uint32_t timer_get_ticks(void);
void timer_wait(uint32_t milliseconds);