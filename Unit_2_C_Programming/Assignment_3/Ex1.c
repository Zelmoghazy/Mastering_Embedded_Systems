#include <stdio.h>
#include <stdlib.h>

#define N 2

int main()
{
    float a[N][N];
    float b[N][N];
    size_t i ;
    size_t j ;
    printf("Enter elements of 1st matrix : \n");
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("Enter a%zu%zu: ",i,j);
            scanf("%f",&a[i][j]);
        }
    }
    printf("Enter elements of 2nd matrix : \n");
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("Enter b%zu%zu: ", i, j);
            scanf("%f",&b[i][j]);
        }
    }
    printf("Sum of Matrix : \n");
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("%.2f  ",a[i][j]+b[i][j]);
        }
        printf("\n");
    }
    
    system("pause");
    return 0;
}