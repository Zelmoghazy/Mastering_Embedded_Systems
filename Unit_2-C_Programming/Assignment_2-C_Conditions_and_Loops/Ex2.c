#include <stdio.h>
#include <stdlib.h>
int main()
{
    char ch;
    printf("Enter an alphabet : ");
    scanf(" %c",&ch);

    switch (ch)
    {
        case 'A':
        case 'a':
        case 'E':
        case 'e':
        case 'I':
        case 'i':
        case 'O':
        case 'o':
            printf("%c is a vowel.\n",ch);
            break;
        default:
            printf("%c is a consonant.\n",ch);
            break;
    }
   
    system("pause");
    return 0;
}