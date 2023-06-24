#ifndef ZCC_ASM_H
#define ZCC_ASM_H


#include "zcc.h"

void asmStartDataSegment();
void asmAddData(char size, char *label, long data);
global_var *getGlobalVar(char *sent);


#endif
