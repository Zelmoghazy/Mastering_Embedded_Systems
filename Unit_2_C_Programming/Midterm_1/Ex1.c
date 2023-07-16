#include <stdio.h>
#include <stdlib.h>

/* c function to take a number and sum all digits */
int sum_digits(int n)
{
    int sum = 0;
    while (n > 0){
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main()
{
    printf("%d\n",sum_digits(123));    
    printf("%d\n",sum_digits(4565));    
    system("pause");
    return 0;
}