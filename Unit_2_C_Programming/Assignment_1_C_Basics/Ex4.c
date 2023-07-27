/* Write C Program to Multiply two Floating Point Number */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a;
    float b;

    printf("Enter two numbers: ");
    scanf("%f %f",&a,&b);

    printf("Product: %.2f\n",a*b);

    system("pause");
    return 0;
}