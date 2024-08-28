#ifndef UTILS_H_
#define UTILS_H_

#define DEBUG  1

#define DEBUG_PRT(fmt, ...)                                                                                     \
    do{                                                                                                         \
        if(DEBUG)                                                                                               \
            fprintf(stderr, "%s:%d:%s(): \n" fmt "\n", __FILE__, __LINE__, __func__ __VA_OPT__(,) __VA_ARGS__); \
    }while(0)

#define NUM_ELEMS(x) ((sizeof(x))/(sizeof((x)[0])))

#define ENUM_GEN(ENUM)     ENUM,
#define STRING_GEN(STRING) #STRING,

#endif /* UTILS_H_ */