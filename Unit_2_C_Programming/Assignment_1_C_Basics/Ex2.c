/* Write C Program to Print a Integer Entered by a User */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int integer;

    printf("Enter an integer: ");
    scanf("%d",&integer);

    printf("You entered: %d\n",integer);

    system("pause");
    return 0;
}