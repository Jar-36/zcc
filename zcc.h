#ifndef ZCC_ZCC_H
#define ZCC_ZCC_H

#include <stdio.h>
#include "libutil/util.h"
#include "asm.h"
extern FILE *srcfp;
extern FILE *asmfp;

typedef struct GLOBAL_VAR{
    char type_size;
    char flags;
    char *name;
    struct GLOBAL_VAR* next;
}global_var;

typedef struct TYPE_LIST{
    char type_size;
    char *typestr;
    struct TYPE_LIST* next;
}type_list;

enum type{
    BYTE=1, WORD, DWORD
};

#define GLOBAL_VAR_DEF_SENT 0
#define GLOBAL_FUNC_DEF_SENT 1

#endif