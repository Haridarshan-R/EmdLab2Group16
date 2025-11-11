#include <stdint.h>
#include "led.h"

void main(void)
{
    GPIO_setup();
    volatile int i;
    resetWS2812();
    ledPosition(10,0,15,0);
    while(1);
}
