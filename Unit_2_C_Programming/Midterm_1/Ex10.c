#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a>b)?a:b;
}

int max_number_of_ones(int n){
    int maximum = 0;
    int counter = 0;
    while (n > 0){
        if (n % 2){
            counter++;
        }else{
            maximum = max(counter, maximum);
            counter = 0;
        }
        n /= 2;
    }
    maximum = max(counter, maximum);
    return maximum;
}

int main()
{
    printf("%d\n",max_number_of_ones(14));
    printf("%d\n",max_number_of_ones(110));
    system("pause");
    return 0;
}