/* Write Source Code to Swap Two Numbers without temp variable. */

#include <stdio.h>
#include <stdlib.h>

void swap (float *a, float *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
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