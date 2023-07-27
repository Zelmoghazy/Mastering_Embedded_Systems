/* Write C Program to Find ASCII Value of a Character */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch;

    printf("Enter a character: ");
    scanf("%c",&ch);
    
    printf("ASCII value of %c = %d\n",ch,(int)ch);

    system("pause");
    return 0;
}