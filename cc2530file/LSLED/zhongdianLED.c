#include <ioCC2530.h>
#define LED1  P1_0


void LEDInit(void)
{
    P1SEL &= ~0x01;
    P1DIR |= 0x01;
    P1 = 0x00;
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
}


void KeyInt()
{
  IEN2 |= 0x10;//P1IE
  P1IEN |= 0X04;
  PICTL |= 0X02;
  EA = 1;
}

#pragma vector = P1INT_VECTOR
__interrupt void P1_ISR(void)
{
  if((P1IFG & 0x04)==0x04)
  {
    
    LED1 = !LED1;
    P1IFG &=~0X04;
    
  }
  P1IF = 0x00;
}
int main(void)
{
  LEDInit();
  KeyInit();
  IEInit();
  while(1)
  {
    
  }
}