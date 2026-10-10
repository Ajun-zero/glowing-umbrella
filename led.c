#include "iocc2530.h"
#define LED P1_0

void delay(unsigned int x)
{
    unsigned int i;
    while (x--)
    {
        for ( i = 0; i < 500; i++);
    }
}

void GPIOInit()
{
    P1SEL &=~0x01;
    P1DIR |=0x01;
}

void main(void)
{
    GPIOInit();
    while (1)
    {
        LED = 1;
        delay(500);
        LED = 0;
        delay(500);
    }
    
}