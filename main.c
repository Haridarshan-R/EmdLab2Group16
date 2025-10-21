#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int series_sum(int k){
    volatile int arr[10];
    arr[9] = 10;
    if (k<=1){
        return 1;
    }
    else{
        return k+series_sum(k-1);
    }
}

void main(void)
{   int a = 12;
    int sum = series_sum(a);
    while(1);
}