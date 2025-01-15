#define MAX_LENGTH 256
#include <stdio.h>
#include <stdlib.h>

int main() {
    char name[MAX_LENGTH + 1];  
    int size = 0;

    char* char_ptr = name;
    
    printf("Enter a string : ");

    fgets(name, MAX_LENGTH, stdin);

    while((*char_ptr)){
        size++;
        char_ptr++;
    }
    printf("Length of string : %d\n",size-1);
    system("pause");
    return 0;
}
