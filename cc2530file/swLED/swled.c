#include <ioCC2530.h>
#define LED  P1_0
#define KEY  P1_2     // 按键接在 P0_1，按下为低电平
void delay(unsigned int x)
{
    unsigned int i;
    while (x--)
    {
        for (i = 0; i < 500; i++);
    }
}
void GPIOInit(void)
{
    /* LED: P1_0 输出 */
    P1SEL &= ~0x01;
    P1DIR |=  0x01;

    /* KEY: P0_1 输入 */
    P1SEL &= ~0x04;   // P0_1 作为普通 GPIO
    P1DIR &= ~0x04;   // P0_1 设为输入
    P0INP &= ~0x04;
    P2INP &= ~0X40;
}
int main(void)
{
    GPIOInit();

    while (1)
    {
        if (KEY == 0)       // 检测按键按下
        {
            delay(10);         // 简单消抖
            if (KEY == 0)      // 确认按下
            {
                LED = 1;       // 按键按下时点亮（按你的板子极性可改）
                while (KEY == 0);  // 等待松手
            }
        }
        else
        {
            LED = 0;           // 没按下时熄灭
        }
    }
}