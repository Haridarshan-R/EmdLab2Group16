#include "led.h"
#include "position.h"
#include "tm4c123gh6pm.h"

#define GREEN       15,0,0
#define RED         0,15,0
#define BLUE        0,0,15
#define YELLOW      15,15,0
#define CYAN        15,0,15
#define MAGENTA     0,15,15
#define WHITE       15,15,15

void main(void)
{
    int8_t color = 0;
    uint8_t pos;
    volatile int i;
    GPIO_setup();
    ledPosition(4,0,0,0);
    while(1)
    {
        pos = position(-12,0);
        if((GPIO_PORTF_DATA_R & 0x01) == 0)
        {
            if(color == 0) ledPosition(pos,RED);
            else if(color == 1) ledPosition(pos,GREEN);
            else if(color == 2) ledPosition(pos,BLUE);
            else if(color == 3) ledPosition(pos,YELLOW);
            else if(color == 4) ledPosition(pos,MAGENTA);
            else if(color == 5) ledPosition(pos,CYAN);
            else
            {
                ledPosition(pos,WHITE);
                color = -1;
            }
            color=color + 1;
            for(i=0;i<200000;i++);
        }
    }
}
