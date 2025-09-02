#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R   = 0x0F;
    GPIO_PORTF_DEN_R  = 0x0F;
    GPIO_PORTF_DIR_R  = 0x0E;
    GPIO_PORTF_PUR_R  = 0x01;
    GPIO_PORTF_DATA_R = 0x02;
    long int x;
    int last_state = 0;
    long int delay = 500000;
    while(1)
    {
        if (((GPIO_PORTF_DATA_R & 0x01) == 0) && (last_state == 0))
        {
            last_state = 1;
            if((GPIO_PORTF_DATA_R & 0x0E) == 0x02) GPIO_PORTF_DATA_R = 0x08;
            else if((GPIO_PORTF_DATA_R & 0x0E) == 0x08) GPIO_PORTF_DATA_R = 0x04;
            else GPIO_PORTF_DATA_R = 0x02;
            x=0;
            while ( x < delay)
            x ++ ;
        }
        if((GPIO_PORTF_DATA_R & 0x01) != 0) last_state = 0;
    }
}