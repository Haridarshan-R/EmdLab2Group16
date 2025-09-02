#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R   = 0x17;
    GPIO_PORTF_DEN_R  = 0x17;
    GPIO_PORTF_DIR_R  = 0x06;
    GPIO_PORTF_PUR_R  = 0x11;
    while(1)
    {
        if ((GPIO_PORTF_DATA_R & 0x11) == 0x11) GPIO_PORTF_DATA_R = 0x00;
        else if ((GPIO_PORTF_DATA_R & 0x11) == 0x01) GPIO_PORTF_DATA_R = 0x02;
        else if ((GPIO_PORTF_DATA_R & 0x11) == 0x10) GPIO_PORTF_DATA_R = 0x04;
        else ((GPIO_PORTF_DATA_R & 0x11) == 0x00) GPIO_PORTF_DATA_R = 0x06;
    }
}