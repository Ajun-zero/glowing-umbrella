#include <ioCC2530.h>
#define LED  P1_0
#define KEY  P1_2   
void delay(unsigned int x)
{
    unsigned int i;
    while (x--)
    {
        for (i = 0; i < 500; i++);
    }
}
void LEDInit(void)
{
    LED = 0;
    P1SEL &= ~0x01;   //设定P1.0为GPIO
    P1DIR |=  0x01;   //设定P1.0为输出
}
void KEYInit(void)
{
    P1SEL &= ~0x04;   // P1_2 作为普通 GPIO
    P1DIR &= ~0x04;   // P1_2 设为输入
    P1INP &= ~0x04; 
    P2INP &= ~0X40;
}
int main(void)
{
    LEDInit();
    KEYInit();
    while (1)
    {
        if (KEY == 0)       // 检测按键按下
        {
            delay(20);         // 简单消抖
            if (KEY == 0)      // 确认按下
            {
              while(!KEY);
              delay(20);
                LED = !LED;       
            }
        }
    }
}