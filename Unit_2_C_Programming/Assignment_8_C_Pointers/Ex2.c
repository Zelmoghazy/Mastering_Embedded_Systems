#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int i;
    
    char Alphabet[26];
    char *ptr = Alphabet;

    for (i = 0; i < 26; i++){
        *(ptr+i)= (char)('A'+ i);
    }

    for (i = 0; i < 26; i++){
        printf("%c ",*(ptr+i));
    }
    printf("\n");
   
    system("pause");
    return 0;
}