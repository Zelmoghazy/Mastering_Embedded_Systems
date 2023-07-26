#define MAX_LENGTH 256
#include <stdio.h>
#include <stdlib.h>

void swap(char *a , char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    char name[MAX_LENGTH + 1];  
    int size = 0;
    int i ;
    int j ;

    char* char_ptr = name;
    
    printf("Enter a string : ");

    fgets(name, MAX_LENGTH, stdin);

    while((*char_ptr)){
        size++;
        char_ptr++;
    }
    
    i = 0;
    j = size-2;

    while(i<j){
        swap(&name[i],&name[j]);
        j--;
        i++;
    }
    printf("Reversed string : %s",name);
    system("pause");
    return 0;
}
