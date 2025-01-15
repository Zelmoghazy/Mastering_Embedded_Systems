#include <stdio.h>
#include <stdlib.h>

int singleNumber(int *a, int n) {
    int xored = 0;
    int i;
    for(i = 0; i < n ; i++){
        xored ^= a[i];
    }
    return xored;
}

int main(void)
{
    int a[7] = {4,2,5,2,5,7,4};
    int b[3] = {4,2,4};
    printf("%d\n",singleNumber(a,sizeof(a)/sizeof(a[0])));
    printf("%d\n",singleNumber(b,sizeof(b)/sizeof(b[0])));
    system("pause");
}

