#include <stdio.h>
#include "Utilities.h"
#include "Config.h"

void symbol_repeat(char str[], size_t size, char symbol) 
{
    size_t i;
    for (i = 0; i < size; i++)
        str[i] = symbol;
    str[size]='\0';
}

void print_frame(const char *title, size_t size, char symbol,char *choice)
{
    printf("\n");
    const char *Label = title;
    char Padding[size+1];
    symbol_repeat(Padding,size,symbol);       
    size_t Length = size - strlen(Label);  
    printf("%*.*s%s%*.*s\n", Length / 2, Length / 2, Padding, Label, (Length + 1) / 2, (Length + 1) / 2, Padding);

    printf("%s\n",MESSAGE_BOX);
    printf("Enter a choice : ");
    scanf(" %c",choice);

    printf("%s\n",Padding);
}

bool is_integer(const char *str) 
{
    if (str == NULL || *str == '\0') {
        return false; 
    }
    if (*str == '-' || *str == '+') {
        str++;
    }
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return false; 
        }
        str++;
    }
    return true; 
}


bool is_float(const char *str) 
{
    if (str == NULL || *str == '\0') {
        return false; 
    }

    if (*str == '-' || *str == '+') {
        str++;
    }

    bool decimalPointFound = false; 

    while (*str != '\0') {
        if ((*str < '0' || *str > '9') && *str != '.') {
            return false; 
        }

        if (*str == '.') {
            if (decimalPointFound) {
                return false; 
            }
            decimalPointFound = true;
        }
        str++;
    }
    return true; 
}
