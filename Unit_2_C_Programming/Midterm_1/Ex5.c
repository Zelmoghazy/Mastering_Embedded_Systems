#include <stdio.h>
#include <stdlib.h>

int number_of_ones(int n){
    int sum = 0;
    while (n > 0){
        if (n % 2){
            sum++;
        }
        n /= 2;
    }
    return sum;
}

int main(void)
{
    printf("%d\n",number_of_ones(5));
    printf("%d\n",number_of_ones(15));
    system("pause");
    return 0;
}