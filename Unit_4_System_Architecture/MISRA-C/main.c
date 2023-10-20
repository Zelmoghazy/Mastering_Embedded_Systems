#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *p = malloc(1024*sizeof(int));
    for (size_t i = 0; i < 1024; i++)
    {
        p[i] = i;
    }
    system("pause");
    return 0;
}