#include <stdio.h>

/* 冒泡排序：对整型数组 arr 进行升序排序，n 为数组元素个数 */
void bubble_sort(int arr[], int n)
{
    int i, j, temp;
    int swapped;  /* 优化标记：本轮是否发生过交换 */

    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        /* 如果本轮没有交换，说明已经有序，提前结束 */
        if (swapped == 0) {
            break;
        }
    }
}

int main(void)
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    bubble_sort(arr, n);

    printf("排序结果：");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
