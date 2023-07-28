#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT,
    FLOAT,
    DOUBLE
} Type;

void pointer_info(void *ptr, Type type)
{
    printf("--------------------------------\n");
    printf("Address of pointer : 0x%p\n",ptr);
    switch (type)
    {
        case INT:
            printf("Content of pointer : %d\n",*((int*)ptr));
            break;
        case FLOAT:
            printf("Content of pointer : %f\n",*((float*)ptr));
            break;
        case DOUBLE:
            printf("Content of pointer : %lf\n",*((double*)ptr));
            break;
        default:
            break;
    }
}

int main(void)
{
    int m = 29;

    printf("Address of m : 0x%p\n",(void*)&m);
    printf("Value of m : %d\n",m);

    int *ab = &m;

    pointer_info(ab,INT);
    m = 34;

    pointer_info(ab,INT);
    *ab = 7;

    printf("--------------------------------\n");
    printf("Address of m : 0x%p\n",(void *)&m);
    printf("Value of m : %d\n",m);

    system("pause");
    return 0;
}