#include <stdio.h>
#include <stdlib.h>

void reverse_array(int *A, int size){
    int i = 0;
    int j = size-1;
    while(i<=j){
        int tmp = A[i];
        A[i++] = A[j];
        A[j--] = tmp;
    }
}

int main(void)
{
   int i;
   int A[5] = {1,2,3,4,5};
   int sizeA = sizeof(A)/sizeof(A[0]);

   reverse_array(A,sizeA);

   for (i = 0; i < sizeA; i++){
        printf("%d ",A[i]);
   }
   printf("\n");

   system("pause");
}