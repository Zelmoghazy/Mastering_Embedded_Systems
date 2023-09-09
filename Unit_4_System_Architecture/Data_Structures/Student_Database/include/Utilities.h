#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include <stddef.h>

#define GET_STRING(str, MAX)              \
    do{                                   \
    int _ch = fgetc(stdin);               \
    if (!(_ch == EOF || _ch == '\n')) {   \
        ungetc(_ch, stdin);               \
    }                                     \
    fgets((str), (MAX), stdin);           \
    (str)[strcspn((str), "\n")] = '\0';   \
    }while(0)                             \

#define SEPERATOR(length)                 \
    for (size_t i = 0; i < (length); i++) \
        printf(TABLE_SYM);                \

void symbol_repeat(char str[], size_t size, char symbol);
void print_frame(const char *title, size_t size, char symbol,void(*func)(void));
bool is_integer(const char *str); 
bool is_float(const char *str);


#endif