#include <stdint.h>
#include "tm4c123gh6pm.h"

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

void main(void)
{
    union
    {
        uint32_t u;     // access as 32-bit raw bits
        float f;        // access as a floating-point number
    } a,b,result;
    a.f = 25;
    b.f = 0.2;
    result.u = f_add(a.u,b.u);
    while (1);
}
