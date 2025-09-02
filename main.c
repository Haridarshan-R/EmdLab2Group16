#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define STCTRL               (*((volatile uint32_t *)0xE000E010))
#define STRELOAD             (*((volatile uint32_t *)0xE000E014))
#define STCURRENT            (*((volatile uint32_t *)0xE000E018))

#define ENABLE   1
#define CLK_SRC  (1<<2)
#define COUNT    (1<<16)
#define RED      (1<<1)
#define BLUE     (1<<2)

void poll_sw1(void);

int main(void)
{
    SYSCTL_RCGC2_R |= 0x20;          // Enable clock to Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R   = 0x1F;        // Unlock PF0–PF4
    GPIO_PORTF_DEN_R  = 0x1F;        // Digital enable
    GPIO_PORTF_DIR_R  = 0x0E;        // PF1–PF3 output, PF0/PF4 input
    GPIO_PORTF_PUR_R  = 0x11;        // Pull-ups for PF0, PF4
    GPIO_PORTF_DATA_R = 0x00;

    STRELOAD  = (1<<24)-1;
    STCURRENT = 0;                   // Clear current
    STCTRL   |= CLK_SRC;             // SysTick with core clock

    while(1)
    {
        poll_sw1();
        STCTRL |= ENABLE;
        while ((STCTRL & COUNT) == 0)
        {
            poll_sw1();
        }
        GPIO_PORTF_DATA_R ^= RED;
        STCTRL &= ~ENABLE;
        STCURRENT = 0;
    }
}

void poll_sw1(void)
{
    if ((GPIO_PORTF_DATA_R & 0x01) == 0) GPIO_PORTF_DATA_R |= BLUE;
    else GPIO_PORTF_DATA_R &= ~BLUE;
}