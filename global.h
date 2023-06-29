//
// Created by aiyu on 23-6-27.
//

#ifndef ZCC_GLOBAL_H
#define ZCC_GLOBAL_H

#include "zcc.h"

void readGlobalVar();
void readGlobalFunction();
function *getFunction(int id);
global_var *getGlobalVar(int id);

extern global_var *headGlobalVar;
extern function *headFunction;

#endif //ZCC_GLOBAL_H
