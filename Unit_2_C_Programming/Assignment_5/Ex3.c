#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 512

void SentenceRev(char *str){
    if((*str) == '\0'){
        return;
    }
    SentenceRev(str+1);
    printf("%c",*str);
}

int main()
{
    char sentence[MAX_LENGTH + 1];  

    printf("Enter a string : ");

    fgets(sentence, MAX_LENGTH, stdin);

    SentenceRev(sentence);
    printf("\n");
   
    system("pause");
    return 0;
}