#include <stdio.h>
#include <stdlib.h>
int main()
{
    size_t n;
    float avg = 0;
    size_t i ;
    printf("Enter the number of data: ");
    scanf("%zu",&n);
    float *A = malloc(sizeof(float)*n);
    for (i = 0; i < n; i++){
        printf("%zu. Enter number: ",i+1);
        scanf("%f",A+i);
    }
    for (i = 0; i < n; i++){
        avg += A[i];
    }
    avg = avg/n;
    printf("Average = %.2f\n",avg);
    free(A);
    system("pause");
    return 0;
}