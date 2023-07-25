#include <stdio.h>
#include <stdlib.h>

#define FORI(size) for(size_t i = 0; i<size;i++)
#define FORJ(size) for(size_t j = 0; j<size;j++)

#define FOREACH(item, array)                          \
    for (int _keep = 1,                               \
             _count = 0,                              \
             _size = sizeof(array) / sizeof *(array); \
         _keep && _count != _size;                    \
         _keep = !_keep, _count++)                    \
        for (item = (array) + _count; _keep; _keep = !_keep)

#define NUM_ELEMS(x) ((sizeof(x))/(sizeof((x)[0])))

#define MAT_AT(A,i,j) (A)[(i)*COLS+(j)]

#define GET_STRING(str, MAX)            \
    int _ch = fgetc(stdin);             \
    if (!(_ch == EOF || _ch == '\n')) { \
        ungetc(_ch, stdin);             \
    }                                   \
    fgets((str), (MAX), stdin);         \
    (str)[strcspn((str), "\n")] = '\0';

#define SET(A, n, v)                               \
    do                                             \
    {                                              \
        size_t i_, n_;                             \
        for (n_ = (n), i_ = 0; n_ > 0; --n_, ++i_) \
            (A)[i_] = (v);                         \
    } while (0)

#define SWAP(x, y, T) \
    do{\
        T tmp = (x); \
        (x) = (y);   \
        (y) = tmp;   \
    }while(0)


#define IMPLIES(x, y) (!(x) || (y))

#define COMPARE_FLOATS(a,b,epsilon) (fabs(a - b) <= epsilon * fabs(a))

#define DEBUG 1

#define DEBUG_PRINT(fmt, ...)                                                               \
    do                                                                                      \
    {                                                                                       \
        if (DEBUG)                                                                          \
            fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
    } while (0)

#define STRINGIZE(...) #__VA_ARGS__

#define CONCAT(x,y) x##y

#define FUNCTION_FACTORY(name, a) \
    int fun_##name(int x)         \
    {                             \
        return (a)*x;             \
    }

FUNCTION_FACTORY(Quadruble,4)

#define GENERIC_MAX(type)               \
    (type) type##_max((type)x, (type)y) \
    {                                   \
        return (x > y) ? x : y;         \
    }

#define C_STANDARD_VERSION() get_c_standard_version()

#define get_c_standard_version()         \
        ({                               \
            const char *version_str;     \
            switch (__STDC_VERSION__)    \
            {                            \
            case 199409L:                \
                version_str = "C95";     \
                break;                   \
            case 199901L:                \
                version_str = "C99";     \
                break;                   \
            case 201112L:                \
                version_str = "C11";     \
                break;                   \
            case 201710L:                \
                version_str = "C17";     \
                break;                   \
            case 202112L:                \
                version_str = "C23";     \
                break;                   \
            default:                     \
                version_str = "Unknown"; \
                break;                   \
            }                            \
            version_str;                 \
        })

#define TEST(condition, ...) ((condition) ? printf("Passed test: %s\n", #condition) : printf(__VA_ARGS__))

int main()
{
    printf("File :%s\n", __FILE__ );
    printf("Date :%s\n", __DATE__ );
    printf("Time :%s\n", __TIME__ );
    printf("Line :%d\n", __LINE__ );
    printf("ANSI :%d\n", __STDC__ );
    printf("%s\n",get_c_standard_version());

    system("pause");
    return 0;
}