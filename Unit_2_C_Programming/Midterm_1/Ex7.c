#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b){
    int sum1 = a*(a+1)/2;
    int sum2 = (b)*(b+1)/2;
    return (sum2-sum1)+a;
}

int main()
{
    printf("%d\n",sum(1,100));
    system("pause");
    return 0;
}