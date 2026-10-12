/* 迭代版：效率高，推荐 */
long fib(int n)
{
    long a = 0, b = 1, t;
    int i;
    if (n <= 1) return n;
    for (i = 2; i <= n; i++) {
        t = a + b;
        a = b;
        b = t;
    }
    return b;
}
