#include <ioCC2530.h>
#define LED1  P1_0
#define LED2 P1_1
#define KEY  P1_2
unsigned char a = 0;
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
}
void delay(int x)
{
  unsigned int i;
  while(x--)
  {
    for(i = 0;i < 500;i++)
    {
      while(a);
    }
        
  }
}
#pragma vector = P1INT_VECTOR
__interrupt void P1_ISR(void)
{
  if((P1IFG & 0x04)==0x04)
  {
    a = !a;
    
  }
  P1IF = 0x00;
}
int main(void)
{
  a=0;
  LEDInit();
  KeyInit();
  IEInit();
  while(1)
  {
    LED1 = 0;
    LED2 = 0;
    delay(500);
    LED1 = 1;
    LED2 = 0;
    delay(500);
    LED1 = 1;
    LED2 = 1;
    delay(500);
    LED1 = 0;
    LED2 = 1;
    delay(500);
  }
}