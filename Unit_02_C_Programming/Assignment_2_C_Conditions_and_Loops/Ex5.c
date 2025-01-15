/* C Program to Check Whether a Character is an Alphabet or not */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch;

    printf("Enter a character : ");
    scanf(" %c",&ch);

    if((ch >= 65 && ch <=  90 ) ||
       (ch >= 97 && ch <= 122 ))
    {
        printf("%c is an alphabet.\n",ch);
    }else{
        printf("%c is not an alphabet.\n",ch);
    }

    system("pause");
    return 0;
}