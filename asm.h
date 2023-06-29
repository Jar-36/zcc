#ifndef ZCC_ASM_H
#define ZCC_ASM_H


#include "zcc.h"

void asmStartDataSegment();
void asmStartCodeSegment();
void asmStartRodataSegment();
void asmAddData(global_var* var, long data);
void asmGlobalLabel(char *label);
void asmExternLabel(char *label);
void asmAddFunction(char *label);

#endif
