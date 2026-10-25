#include <stdio.h>

unsigned long long jiecheng(unsigned int i)
{
    if (i <= 1)
    {
        return 1;
    }

    return (unsigned long long)i * jiecheng(i - 1);
}

int main(void)
{
    while (1)
    {
         unsigned int sr;

        if (scanf("%u", &sr) != 1)
        {
           return 1;
        }

        printf("%llu\n", jiecheng(sr));

    
    }
    
   
}