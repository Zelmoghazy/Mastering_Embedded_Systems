/* C Program to Insert an element in an Array */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 64
int size = 0;

int main()
{
    size_t i;
    int A[MAX_SIZE];
    int value;
    int location;

    printf("Enter number of elements : ");
    scanf("%d",&size);

    for (i = 0; i < size; i++){
        A[i] = i+1;
        printf("%d  ",A[i]);
    }
    printf("\n");

    printf("Enter element to be inserted : ");
    scanf("%d",&value);
    
    printf("Enter the location : ");
    scanf("%d",&location);

    if (location - 1 != size){
        for (i = size; i > location-1; i--){
            A[i] = A[i - 1];
        }
        A[location-1] = value;
        size++;
    }else{
        A[location-1] = value;
        size++;
    }

    for (i = 0; i < size; i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}