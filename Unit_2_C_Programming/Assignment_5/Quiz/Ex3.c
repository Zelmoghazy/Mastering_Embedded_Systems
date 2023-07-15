/*  Write a C function that reverse an input array */

void reverse_array(int *A, int size){
    int i = 0;
    int j = size-1;
    while(i<=j){
        int tmp = A[i];
        A[i++] = A[j];
        A[j--] = tmp;
    }
}