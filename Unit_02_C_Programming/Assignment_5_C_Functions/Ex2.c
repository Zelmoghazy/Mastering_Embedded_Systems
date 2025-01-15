#include <stdio.h>
#include <stdlib.h>

long long Factorial(int n)
{
    if (n == 0)
        return 1;
    else
        return Factorial(n - 1) * n;
}

int main()
{
    int n;
    printf("Enter a positive integer: ");
    scanf("%d",&n);
    if (n>0)
        printf("Factorial of %d = %lld\n",n,Factorial(n));
    else
        printf("Error! Positive only.");
    
    system("pause");
    return 0;
}