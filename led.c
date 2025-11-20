#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "led.h"

void GPIO_setup(void)
{
    SYSCTL_RCGCGPIO_R |= (1<<5);     // enable clock for Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x1F;
    GPIO_PORTF_DEN_R |= 0x1F;
    GPIO_PORTF_DIR_R |= 0x0E;         // PF1–3 output
    GPIO_PORTF_PUR_R |= 0x11;
    GPIO_PORTF_DATA_R &= ~LED_PIN;
}


void sendBit(uint8_t bit)
{
    volatile int i = 0;
    if(bit)
    {
        GPIO_PORTF_DATA_R |= LED_PIN;         // HIGH
        i = i + 1;
        GPIO_PORTF_DATA_R &= ~LED_PIN;        // LOW
        i = i + 1;
    }
    else
    {
        GPIO_PORTF_DATA_R |= LED_PIN;         // HIGH
        GPIO_PORTF_DATA_R &= ~LED_PIN;        // LOW
        i = i + 1;
    }
}


void sendByte(uint8_t byte)
{
    int i;
    for(i = 7; i >= 0; i--)
        sendBit((byte >> i) & 1);
}


void sendColor(uint8_t G, uint8_t R, uint8_t B)
{
    sendByte(G);
    sendByte(R);
    sendByte(B);
}


void resetWS2812(void)
{
    volatile int i;
    GPIO_PORTF_DATA_R &= ~LED_PIN;
    for(i = 0; i < 64000; i++); // >50 µs reset
}

void ledPosition(uint8_t pos,uint8_t G, uint8_t R, uint8_t B)
{
    if(pos>16) pos = 16;
    volatile int i;
    for(i = 0; i < (pos-1); i++)
        sendColor(0,0,0);
    sendColor(G,R,B);
    for(i = pos; i < 16; i++)
            sendColor(0,0,0);
    resetWS2812();
}
