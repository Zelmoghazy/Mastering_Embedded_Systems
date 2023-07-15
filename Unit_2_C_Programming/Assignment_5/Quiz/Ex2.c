/* Write a program for swapping two arrays with different lengths */

#include <stdio.h>
#include <stdlib.h>

void swapArray(int a[],int b[], size_t size) {
    while (size > 0) {
        size--;
        int tmp = a[size];
        a[size] = b[size];
        b[size] = tmp;
    }
}

int main(void)
{
    int i;
    int A[] = {1,2,3,4,5,6,7};
    int B[] = {9,8,7};
    int Size_A = sizeof(A)/sizeof(A[0]);
    int Size_B = sizeof(B)/sizeof(B[0]);
    int min_size = (Size_A < Size_B) ? Size_A:Size_B;
    swapArray(A,B,min_size);
    for (i = 0; i < Size_A; i++)
    {
        printf("%d ",A[i]);
    }
    printf("\n");
    for (i = 0; i < Size_B; i++)
    {
        printf("%d ",B[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}