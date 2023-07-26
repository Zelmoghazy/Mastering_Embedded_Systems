/* Function that return the index of last occurence of a number in a given array */
int find_last_occurence(int *A,int size, int n){
    int res = -1;
    for (int i = 0; i < size; i++)
        if(A[i] == n)
            res = i;
    return res;
}