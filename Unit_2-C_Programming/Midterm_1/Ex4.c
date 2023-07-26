#include <stdio.h>
#include <stdlib.h>

int reverse_digits(int n){
    int res = 0;
    while(n){
        res = res*10 + n%10;
        n /= 10;
    }
    return res;
}

int main()
{
    printf("%d\n",reverse_digits(2457));
    printf("%d\n",reverse_digits(1057));
    system("pause");
    return 0;
}