#ifndef ZCC_CTREE_H
#define ZCC_CTREE_H

#include "zcc.h"

typedef struct GLOBAL_VAR{
    char type_size;
    char flags;
    int id;
    char *name;
    struct GLOBAL_VAR* next;
}global_var;

global_var *constructGlobalVar(char *sent);
function *constructGlobalFunction(char *sent);
void processParam(char *p, function *func);

#endif
