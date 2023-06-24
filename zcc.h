#ifndef ZCC_ZCC_H
#define ZCC_ZCC_H

#include <stdio.h>
#include "libutil/util.h"
extern FILE *srcfp;
extern FILE *asmfp;

typedef struct GLOBAL_VAR{
    char type_size;
    char flags;
    char *name;
    long value;
}global_var;

// global var flags
//   high<<<<<bit                                                           bit>>>>>low
//    b7     |     b6   |    b5    |     b4   |     b3   |   b2   |   b1   |   b0  |
//  reserved | reserved | reserved | register | volatile | extern | static | const |

typedef struct TYPE_LIST{
    char type_size;
    char *typestr;
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