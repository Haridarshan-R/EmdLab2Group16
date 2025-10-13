#include <stdint.h>
#include "tm4c123gh6pm.h"

struct
{
    uint32_t u;     // 32-bit IEEE format computed by fadd
    float f;        // reference result computed by c = a + b
} buf[0x100];
int index;

uint32_t f_add(uint32_t a, uint32_t b)
{
    uint32_t e1,e2,m1,m2,result,e;
    //Unpacking
    e1 = (a >> 23) & 0x000000FF;
    e2 = (b >> 23) & 0x000000FF;
    m1 = (a & 0x007FFFFF) | 0x00800000;
    m2 = (b & 0x007FFFFF) | 0x00800000;

    //Exponent Check
    if(e1>e2)
    {
        m2 = m2 >> (e1-e2);
        e  = e1;
    }
    else
    {
        m1 = m1 >> (e2-e1);
        e  = e2;
    }

    //Addition and Overflow Check
    result = m1 + m2;
    if((result & 0x01000000) != 0)
    {
        e = e + 1;
        result = result >> 1;
    }
    result = (result & 0x007FFFFF) | (e<<23);
    return result;
}

void fadd_test(float a, float b)
{
    union
    {
        uint32_t u;     // access as 32-bit raw bits
        float f;        // access as a floating-point number
    } A, B, C;

    float c;

    A.f = a;
    B.f = b;

    C.u = f_add(A.u, B.u);       // output of asm code
    c = a + b;                  // reference output by C code

    if (index < 0x100)
    {
        buf[index].u = C.u;     // asm result
        buf[index].f = c;       // C result
        index++;
    }

    return;
}

void main(void)
{
    fadd_test(100.0f, 0.25f);       // 100.25f  (0x42C88000)
    fadd_test(1.5f, 1.5f);          // 3.0f     (0x40400000)
    fadd_test(2.75f, 1.5f);         // 4.25f    (0x40880000)
    fadd_test(1024.0f, 1.0f);       // 1025.0f  (0x44802000)
    fadd_test(1.0f, 0.125f);        // 1.125f   (0x3F900000)
    fadd_test(65536.0f, 256.0f);    // 65792.0f (0x47808000)

    while (1);
}
