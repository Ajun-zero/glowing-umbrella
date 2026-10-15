#include <stdio.h>
#include <string.h>

int main(void) {
    // memset：把数组全部清零
    int arr[10];
    memset(arr, 0, sizeof(arr));
    printf("arr[0] = %d\n", arr[0]);  // 0

    // memcpy：拷贝内存
    char src[] = "memory copy";
    char dest[20];
    memcpy(dest, src, strlen(src) + 1);  // +1 连同 '\0' 一起拷贝
    printf("dest = %s\n", dest);

    // 拷贝整型数组
    int a[5] = {1, 2, 3, 4, 5};
    int b[5];
    memcpy(b, a, sizeof(a));
    printf("b[4] = %d\n", b[4]);      // 5

    return 0;
}
