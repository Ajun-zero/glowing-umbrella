#include <ioCC2530.h>
#define LED1  P1_0
#define LED2 P1_1
#define KEY  P1_2
unsigned int a;
void LEDInit(void)
{
    P1SEL &= ~0x03;
    P1DIR |= 0x03;
    P1 &= ~0x00;
}
void KeyInit(void)
{
  P1SEL &= ~0x04;
  P1DIR &= ~0x04;
  P1INP &= ~0x04;
  P2INP &= ~0x40;
}
void IEInit()
{
  EA = 1;
  IEN2  |= 0x10;
  P1IEN |= 0x04;
  PICTL |= 0x02;
}]
#pragma vector = P1INT_VECTOR
__interrupt void P1_ISR(void)
{
  if((P1IFG & 0x04)==0x04)
  {
    a++;
    P1IFG &=~0x04;
    if(a == 4)
    {
      a = 1;
    }
    P1IF = 0x00;
  }
}
int main(void)
{
  
  LEDInit();
  KeyInit();
  IEInit();
  while(1)
  {
    if(a == 1)
    {
      LED1 = 1;
      LED2 = 0;
    }
    else if(a == 2)
    {
      LED1 = 0;
      LED2 = 1;
    }
    else if(a == 3)
    {
      LED1 = 0;
      LED2 = 0;
    }
    else
    {
      LED1 = 0;
      LED2 = 0;
    }
  }
}