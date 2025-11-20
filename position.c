#include "position.h"

uint8_t position(float x, float y)
{
    float z;
    if(x!=0) z = y/x;
    else
    {
        if( y >= 0 ) return 1;
        else         return 9;
    }

    if(x>0)
    {
        if(y>=0)
        {
            if     (z<0.1989)   return 5;
            else if(z<0.6681)   return 4;
            else if(z<1.4966)   return 3;
            else if(z<5.027)    return 2;
            else                return 1;
        }

        else
        {
            if     (z>-0.1989)   return 5;
            else if(z>-0.6681)   return 6;
            else if(z>-1.4966)   return 7;
            else if(z>-5.027)    return 8;
            else                 return 9;
        }
    }

    else
    {
        if(y<0)
        {
            if     (z<0.1989)   return 13;
            else if(z<0.6681)   return 12;
            else if(z<1.4966)   return 11;
            else if(z<5.027)    return 10;
            else                return 9;
        }

        else
        {
            if     (z>-0.1989)   return 13;
            else if(z>-0.6681)   return 14;
            else if(z>-1.4966)   return 15;
            else if(z>-5.027)    return 16;
            else                 return 1;
        }
    }
}
