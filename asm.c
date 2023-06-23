#include "zcc.h"
#include <stdio.h>

void asmStartDataSegment(){
    asmRollback();
    fputs("BITS 32\nSECTION .data\n", asmfp);
}