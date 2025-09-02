#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define STCTRL               (*((volatile uint32_t *)0xE000E010))
#define STRELOAD             (*((volatile uint32_t *)0xE000E014))
#define STCURRENT            (*((volatile uint32_t *)0xE000E018))

#define ENABLE   1
#define CLK_SRC (1<<2)
#define COUNT   (1<<16)
#define RED     (1<<1)
int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R   = 0x0F;
    GPIO_PORTF_DEN_R  = 0x0F;
    GPIO_PORTF_DIR_R  = 0x0E;
    GPIO_PORTF_PUR_R  = 0x11;
    GPIO_PORTF_DATA_R = 0x00;
    STRELOAD          = (1<<23);
    STCTRL           |= CLK_SRC;
    while(1)
    {
        STCTRL      |= ENABLE;
        while ((STCTRL & COUNT) == 0);
        GPIO_PORTF_DATA_R ^= RED;
        STCTRL      &= ~ENABLE;
        STCURRENT    = 0;
    }
}