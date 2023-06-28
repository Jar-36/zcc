#ifndef ZCC_ZCC_H
#define ZCC_ZCC_H

#include <stdio.h>

extern FILE *srcfp;
extern FILE *asmfp;

typedef struct GLOBAL_VAR{
    char type_size;
    char flags;
    int id;
    char *name;
    struct GLOBAL_VAR* next;
}global_var;

typedef struct PARAM{
    char type;
    int id;
}param;

typedef struct FUNCTION{
    char return_type;
    int id;
    char *name;
    int param_count;
    param param_list[];
}function;

// global var flags
//   high<<<<<bit                                                           bit>>>>>low
//    b7     |     b6   |    b5    |     b4   |     b3   |   b2   |   b1   |   b0  |
//  reserved | reserved | reserved | reserved | reserved | extern | static | const |

typedef struct TYPE_LIST{
    char type_size;
    int id;
    struct TYPE_LIST* next;
}type_list;

#define BYTE 1
#define WORD 2
#define DWORD 3
#define ARRAY 4
#define POINTER 5

#define GLOBAL_VAR_DEF_SENT 0
#define GLOBAL_FUNC_DEF_SENT 1

#endif
