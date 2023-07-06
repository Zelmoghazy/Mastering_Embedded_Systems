#include <stdio.h>
#include <stdlib.h>

int power(int x, int n)
{
    if (n < 0)
        return (1 / power(x, n));
    if (n == 0)
        return 1;
    if (n % 2 == 0)
        return power(x * x, n / 2);
    else
        return power(x * x, n / 2) * x;
}

int main()
{
    int a;
    int n;
    printf("Enter a base number : ");
    scanf("%d",&a);
    printf("Enter power number : ");
    scanf("%d",&n);
    
    printf("%d^%d = %d\n", a,n,power(a, n));
    system("pause");
    return 0;
}