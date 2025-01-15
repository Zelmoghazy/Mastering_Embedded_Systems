/* Write Source Code to Swap Two Numbers */

#include <stdio.h>
#include <stdlib.h>

void swap (float *a, float *b){
    float temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{   
    float a;
    float b;

    printf("Enter value of a : ");
    scanf("%f",&a);

    printf("Enter value of b : ");
    scanf("%f",&b);

    swap(&a,&b);

    printf("After swapping, value of a = %.2f\n", a);
    printf("After swapping, value of b = %.2f\n", b);
    
    system("pause");
    return 0;
}