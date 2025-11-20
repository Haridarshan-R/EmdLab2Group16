#include <stdint.h>
#include "tm4c123gh6pm.h"

#define SSE (1<<1)
#define DSS (0x7)
#define SPO (1<<6)
#define SPH (1<<7)

void main(void)
{
    SYSCTL_RCGCSSI_R    |= (1<<2); //CLOCK to module 2 SSI
    SYSCTL_RCGCGPIO_R   |= (1<<1); //CLOCK to port B
    GPIO_PORTB_LOCK_R    = 0x4C4F434B;
    GPIO_PORTB_CR_R     |= 0xF0;
    GPIO_PORTB_AFSEL_R  |= (0xF << 4);    //Selecting alternative functions for pin 4,5,6,7
    GPIO_PORTB_PCTL_R   &= 0x0000FFFF;
    GPIO_PORTB_PCTL_R   |= 0x22220000;    //Selecting SSI function
    GPIO_PORTB_DR2R_R   |= 0xF0;
    GPIO_PORTB_PUR_R    |= 0xF0;
    GPIO_PORTB_DEN_R    |= 0xF0;

    SSI2_CR1_R          &= ~SSE;
    SSI2_CR1_R           = 0x00;
    SSI2_CC_R            = 0x00;
    SSI2_CPSR_R          = 0x02;
    SSI2_CR0_R          &= ~(0xFFFF);
    SSI2_CR0_R          |= DSS | SPO;
    SSI2_CR1_R          |= SSE;
    volatile int i;
    while(1)
    {
        SSI2_DR_R   =   0x71;
        for(i=0;i<160;i++);
    }
}
