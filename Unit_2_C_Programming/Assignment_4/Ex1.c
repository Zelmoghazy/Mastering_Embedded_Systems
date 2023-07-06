#define MAX_LENGTH 256
#include <stdio.h>
#include <stdlib.h>

int main() {
    char name[MAX_LENGTH + 1];  
    int ch;
    int freq = 0;

    char* char_ptr = name;
    
    printf("Enter a string : ");

    /* scanf("%256[^\n]",name);*/
    fgets(name, MAX_LENGTH, stdin);

    printf("Enter a character to find frequency : ");
    ch = getchar();
    while(*char_ptr){
        if((*char_ptr) == (char)ch){
            freq++;
        }
        char_ptr++;
    }

    printf("Frequency of %c is %d\n", (char)ch, freq);
    system("pause");
    return 0;
}
