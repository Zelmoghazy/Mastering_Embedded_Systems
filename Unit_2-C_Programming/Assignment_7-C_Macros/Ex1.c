#include <stdio.h>

#define macro(n, a, i, m) m##a##i##n
#define START macro(n,a,i,m)

int START()
{
    printf("Test");    
    system("pause");
    return 0;
}