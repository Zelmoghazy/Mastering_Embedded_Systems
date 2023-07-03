#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int i;
    int sum;
    printf("Enter an integer: ");
    scanf("%d",&n);
    sum = 0; 
    for (i = 1; i <= n; i++)
        sum += i;
    printf("Sum = %d\n",sum);    
    
    system("pause");
    return 0;
}