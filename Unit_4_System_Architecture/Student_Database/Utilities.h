#define GET_STRING(str, MAX)              \
    do{                                   \
    int _ch = fgetc(stdin);               \
    if (!(_ch == EOF || _ch == '\n')) {   \
        ungetc(_ch, stdin);               \
    }                                     \
    fgets((str), (MAX), stdin);           \
    (str)[strcspn((str), "\n")] = '\0';   \
    }while(0)                             \


void symbol_repeat(char str[], size_t size, char symbol) {
    size_t i;
    for (i = 0; i < size; i++)
        str[i] = symbol;
    str[size]='\0';
}

void print_frame(const char *str, const char *title, size_t size, char symbol){
    const char *Label = title;
    char Padding[size+1];
    symbol_repeat(Padding,size,symbol);       
    size_t Length = size - strlen(Label);  
    printf("%*.*s%s%*.*s\n", Length / 2, Length / 2, Padding, Label, (Length + 1) / 2, (Length + 1) / 2, Padding);
    printf("%s\n",str);
    printf("%s\n",Padding);
}
