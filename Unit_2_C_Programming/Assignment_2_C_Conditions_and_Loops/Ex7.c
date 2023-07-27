/* C Program to Find Factorial of a Number */

#include <stdio.h>
#include <stdlib.h>

int fact(int n)
{
    if (n <= 1)
        return 1;
    else
        return fact(n - 1) * n;
}

int main()
{   
    int n;
    
    printf("Enter an integer: ");
    scanf("%d",&n);

    if(n>=0)
        printf("Factorial = %d\n",fact(n));
    else
        printf("Error!! Factorial of negative numbers doesnt exist.\n");
        
    system("pause");
    return 0;
}