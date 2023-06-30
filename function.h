#ifndef ZCC_FUNCTION_H
#define ZCC_FUNCTION_H

#include "zcc.h"

typedef struct PARAM{
    char type;
    int id;
    int PTR; // 0 for non-ptr; 1 for ptr; 2 for ptr of ptr
    struct PARAM* next;
}param;

typedef struct FUNCTION{
    char return_type; // 0 for non-ptr; 1 for ptr; 2 for ptr of ptr
    int retPTR;
    int id;
    char *name;
    char isStatic;
    char isExternal;
    int param_count;
    int char_index;
    param *param_list_head;
    struct FUNCTION* next;
}function;

void compileFunction(function *func);

typedef struct LOCAL_VAR{
    int id;
    char PTR;
    char type_size;
    int esp;
    struct LOCAL_VAR* next;
}local_var;

#endif
