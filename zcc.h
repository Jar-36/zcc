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

typedef struct FIELD_VAR{
    struct GLOBAL_VAR* core;
    int esp;
    struct FIELD_VAR* next;
}field_var;

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

// global var flags
//   high<<<<<bit                                                           bit>>>>>low
//    b7     |     b6   |    b5    |     b4     |    b3   |   b2   |   b1   |   b0  |
//  reserved | reserved | reserved | PTR OF PTR | pointer | extern | static | const |

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
