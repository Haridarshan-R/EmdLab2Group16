#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define red_led   (1<<1)
#define blue_led  (1<<2)
#define green_led (1<<3)

int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;      // Enable clock to Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // Unlock commit register
    GPIO_PORTF_CR_R   = 0x1F;            // Make PortF0 configurable
    GPIO_PORTF_DEN_R  = 0x1F;            // Enable digital pins on Port F
    GPIO_PORTF_DIR_R  = 0x0E;            // Set PF1-3 as outputs, PF0 & PF4 as inputs
    GPIO_PORTF_PUR_R  = 0x11;            // Enable pull-ups on PF0 and PF4

    GPIO_PORTF_DATA_R = 0x0;             // Turn LEDs off

    while(1)
    {
        if((GPIO_PORTF_DATA_R & 0x11)==0x00) {
            GPIO_PORTF_DATA_R |= green_led;  // Both switches pressed
        }
        else if((GPIO_PORTF_DATA_R & 0x11)==0x10) {
            GPIO_PORTF_DATA_R |= blue_led;   // Switch PF4 pressed
        }
        else if((GPIO_PORTF_DATA_R & 0x11)==0x01) {
            GPIO_PORTF_DATA_R |= red_led;    // Switch PF0 pressed
        }
        else {
            GPIO_PORTF_DATA_R = 0x00;        // No switches pressed
        }
    }
}