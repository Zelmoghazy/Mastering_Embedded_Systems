#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 15

int main()
{
    int i;
    int size;
    int A[MAX_SIZE];
    int *ptr = A;

    printf("Input the number of elements to store in the array (max %d) : ",MAX_SIZE);
    scanf("%d",&size);

    printf("Input %d number of elements in the array : \n",size);

    for (i = 0; i < size; i++){
        printf("Element - %d : ",i+1);
        scanf("%d",ptr);
        ptr++;
    }
    ptr--;

    printf("The elements of array in reverse order are :\n");

    for (i = size-1; i >= 0; i--){
        printf("Element - %d : ",i+1);
        printf("%d\n",*ptr);
        ptr--;
    }   
    
    system("pause");
    return 0;
}