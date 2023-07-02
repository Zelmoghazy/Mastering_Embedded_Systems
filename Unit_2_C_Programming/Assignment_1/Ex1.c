#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void repeatSymbol(char str[], size_t size, char symbol) {
    size_t i;
    for (i = 0; i < size; i++)
        str[i] = symbol;
    str[size]='\0';
}

void print_with_padding(const char *str, const char *title, size_t size, char symbol){
    const char *Label = title;
    char *Padding = malloc(sizeof(char)*size+1);
    repeatSymbol(Padding,size,symbol);       
    size_t Length = size - strlen(Label);  
    printf("%*.*s%s%*.*s\n", Length / 2, Length / 2, Padding, Label, (Length + 1) / 2, (Length + 1) / 2, Padding);
    printf("%s\n",str);
    printf("%s\n",Padding);
    free(Padding);
}

int main() {
    print_with_padding("C Programming","Console-output",50,'#');
    system("pause");
    return 0;
}
