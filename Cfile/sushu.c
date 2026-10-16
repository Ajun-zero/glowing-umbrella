#include <stdio.h>
#include <stdbool.h>

// 判断 n 是否为素数
bool is_prime(int n) {
    if (n < 2) return false;          // 0、1 和负数都不是素数
    for (int i = 2; i < n; i++) {
        if (n % i == 0) return false; // 找到因子，不是素数
    }
    return true;
}

int main(void) {
    for (int i = 1; i <= 20; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}
