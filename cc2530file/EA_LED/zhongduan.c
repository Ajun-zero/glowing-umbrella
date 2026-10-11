#include "ioCC2530.h"
#define LED1 P1_0
#define LED2 P1_1
unsigned int a;

void initial_gpio()
{
  P1SEL &= ~0x07;
  P1DIR |= 0X03;
  P1DIR &= ~0X04;
  P1 = 0x00;
  P1INP &= ~0x04;
  P2INP &= ~0x40;
}
void initial_interrupt()
{
  EA = 1;
  IEN2 |= 0x10;
  P1IEN |= 0x04;
  PICTL |= 0x02;
}

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
  
  initial_gpio();
  initial_interrupt();
  while(1)
  {
    if(a == 1)
    {
      LED1 = 1;
    }
    if(a == 2)
    {
      LED1 = 0;
      LED2 = 1;
    }
    if(a == 3)
    {
      LED2 = 0;
    }
  }
}