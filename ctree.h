#ifndef ZCC_CTREE_H
#define ZCC_CTREE_H

#include "zcc.h"

global_var *constructGlobalVar(char *sent);
function *constructGlobalFunction(char *sent);
void processParam(char *p, function *func);

#endif
