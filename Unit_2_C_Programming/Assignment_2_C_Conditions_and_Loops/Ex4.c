/* C Program to Check Whether a Number is Positive or Negative */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n;

    printf("Enter a number : ");
    scanf("%f", &n);

    if (n == 0)
        printf("You entered zero.\n");
    else if (n > 0)
        printf("%.2f is positive.\n",n);
    else
        printf("%.2f is negative.\n",n);
        
    system("pause");
    return 0;
}