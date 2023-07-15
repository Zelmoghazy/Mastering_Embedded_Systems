#include <stdio.h>
#include <stdlib.h>

/* Value of kth least significant bit */
int LSB(int num, int k)
{
    int res;
    res = (num>>(k-1))&1;
    return res;
}

int main()
{
    int a = 23;
    printf("%d\n",LSB(a,4));
    system("pause");
    return 0;
}