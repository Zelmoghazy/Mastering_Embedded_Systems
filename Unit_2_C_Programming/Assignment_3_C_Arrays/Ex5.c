#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 64

int main()
{
    size_t size = 0;
    size_t i;
    int value;
    bool flag = false;
    int A[MAX_SIZE];

    printf("Enter number of elements : ");
    scanf("%zu",&size);

    for (i = 0; i < size; i++){
        A[i] = (i+1)*11;
        printf("%d  ",A[i]);
    }
    printf("\n");

    printf("Enter element to be searched : ");
    scanf("%d",&value);

    for (i = 0; i < size; i++){
        if(A[i]==value){
            printf("Found at the location = %zu\n",i+1);
            flag = true;
        }
    }

    if(!flag) printf("Not found!!\n");

    system("pause");
    return 0;
}