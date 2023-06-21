#include <stdio.h>
#include "libutil/util.h"
extern FILE *srcfp;
extern FILE *asmfp;

struct global_var_t{
    char type;
    char *name;
    struct global_var_t* next;
}GLOBAL_VAR;

enum type{
    BYTE=1, WORD, DWORD
};

#define HEAD 0
#define CURR 1
