#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    printf("Enter an integer you want check: ");
    scanf("%d",&n);
    if(n%2==0)
        printf("%d is even.\n",n);
    else
        printf("%d is odd.\n",n);
    return 0;
}