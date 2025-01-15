#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64

#define GET_STRING(str, MAX)            \
    do{                                 \
    int _ch = fgetc(stdin);             \
    if (!(_ch == EOF || _ch == '\n')) { \
        ungetc(_ch, stdin);             \
    }                                   \
    fgets((str), (MAX), stdin);         \
    (str)[strcspn((str), "\n")] = '\0'; \
    }while(0)                           \

void print_reverse(char* str)
{
    size_t size = strlen(str);
    char *start = str;
    char *end = str+size-1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    printf("%s\n",str);
}

int main()
{
    char string[MAX_SIZE];

    printf("Input a string : ");
    GET_STRING(string,MAX_SIZE);

    print_reverse(string);
    
    system("pause");
    return 0;
}