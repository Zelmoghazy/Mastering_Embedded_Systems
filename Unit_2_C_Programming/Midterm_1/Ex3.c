#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool IsPrime(int n){
    int i;
    if(n <= 1)
        return false;
    for(i = 2; (i * i) <= n; i++){
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    int a;
    int b;  
    int i;
    printf("Enter two numbers(intervals): ");
    scanf("%d",&a);
    scanf("%d",&b);
    printf("Prime Numbers between %d and %d are: ",a,b);
    for (i = a; i < b; i++){
        if(IsPrime(i)){
            printf("%d ",i);
        }
    }
    printf("\n");
    system("pause");
    return 0;
}