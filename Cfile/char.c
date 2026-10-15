#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[50] = "Hello";
    char str2[] = "World";
    char buf[100];

    // strlen：求长度
    printf("str1 长度: %zu\n", strlen(str1));   // 5

    // strcpy：复制
    strcpy(buf, str1);
    printf("复制后 buf: %s\n", buf);            // Hello

    // strcat：拼接
    strcat(buf, " ");
    strcat(buf, str2);
    printf("拼接后 buf: %s\n", buf);            // Hello World

    // strcmp：比较
    if (strcmp(str1, "Hello") == 0) {
        printf("str1 等于 \"Hello\"\n");
    }
    printf("strcmp(\"abc\", \"abd\") = %d\n", strcmp("abc", "abd")); // 负数

    return 0;
}
