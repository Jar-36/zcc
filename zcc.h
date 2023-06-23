#ifndef ZCC_ZCC_H
#define ZCC_ZCC_H

#include <stdio.h>
#include "libutil/util.h"
#include "asm.h"
extern FILE *srcfp;
extern FILE *asmfp;

struct global_var_t{
    char type_size;
    char flags;
    char *name;
    struct global_var_t* next;
}GLOBAL_VAR;

struct type_list_t{
    char type_size;
    char *typestr;
    struct type_list_t* next;
}TYPE_LIST;

enum type{
    BYTE=1, WORD, DWORD
};

#define GLOBAL_VAR_DEF_SENT 0
#define GLOBAL_FUNC_DEF_SENT 1

#endif