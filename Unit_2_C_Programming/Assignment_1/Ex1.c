#include <stdio.h>
#include <string.h>

void print_with_padding(const char *str){
    const char *Console = "Console-output";       
    const char *padding = "##################################################";
    size_t targetStrLen = strlen(padding);                 

    size_t padLen = targetStrLen - strlen(Console);  

    printf("%*.*s%s%*.*s\n", padLen / 2, padLen / 2, padding, Console, (padLen + 1) / 2, (padLen + 1) / 2, padding);
    printf("%s\n",str);
    printf("%s\n",padding);
}

int main() {
    print_with_padding("C Programming");
    return 0;
}
