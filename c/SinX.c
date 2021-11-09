#include <stdio.h>

// sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ... + (-1)^(n-1) x^(2n-1) / (2n-1)!
// Input a float number x and an integer n, then calculate sin(x), output 8 digits after dot.

int main()
{
    double sinx, x, term;
    int n;
    scanf("%lf %d", &x, &n);
    sinx = term = x;
    // [1, n-1] x 2 + 1 -> [1, 2n - 1]
    for (int i = 1; i < n; i++)
    {
        term *= -x * x / (i * 2) / (i * 2 + 1);
        if (term > -1e-9 && term < 1e-9) // precision
            break;
        sinx += term;
    }

    printf("%.8lf", sinx);

    return 0;
}
