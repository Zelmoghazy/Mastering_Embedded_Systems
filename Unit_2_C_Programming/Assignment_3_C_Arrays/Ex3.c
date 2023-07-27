/* C Program to Find Transpose ofa Matrix */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t i;
    size_t j;
    size_t rows, columns;
    
    printf("Enter number of rows and columns of matrix: ");
    scanf("%zu", &rows);
    scanf("%zu", &columns);

    /* Dynamic Allocation */
    float **A = malloc(rows * sizeof(float *));
    for (i = 0; i < rows; i++) {
        A[i] = malloc(columns * sizeof(float));
    }

    printf("Enter elements of matrix : \n");
    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++){
            printf("Enter elements a%zu%zu: ",i+1,j+1);
            scanf("%f",&A[i][j]);
        }
    }

    printf("Entered Matrix : \n");
    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++){
            printf("%.2f  ",A[i][j]);
        }
        printf("\n");
    }

    printf("Transposed Matrix : \n");
    for (i = 0; i < columns; i++){
        for (j = 0; j < rows; j++){
            printf("%.2f  ",A[j][i]);
        }
        printf("\n");
    }

    /* Free Allocated Memory */
    for (i = 0; i < rows; i++) {
        free(A[i]);
    }
    free(A);

    system("pause");
    return 0;
}