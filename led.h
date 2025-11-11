#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define LED_PIN   (1<<1)    // PF1

void GPIO_setup(void);
void sendBit(uint8_t bit);
void sendByte(uint8_t byte);
void sendColor(uint8_t G, uint8_t R, uint8_t B);
void resetWS2812(void);
void ledPosition(uint8_t pos,uint8_t G, uint8_t R, uint8_t B);

#endif
