/* C Program to Find the Largest Number Among Three Numbers */

#include <stdio.h>
#include <stdlib.h>

float LargestOfThree(float a, float b, float c) {
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

int main()
{
    float a,b,c;

    printf("Enter three numbers: ");
    scanf("%f",&a);
    scanf("%f",&b);
    scanf("%f",&c);

    printf("Largest number = %.2f\n",LargestOfThree(a,b,c));    

    system("pause");
    return 0;
}