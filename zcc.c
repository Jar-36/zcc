#include <stdio.h>
#include "zcc.h"


FILE *srcfp;
FILE *asmfp;

int main(){
    loggerf(INFO, "start compile");
    srcfp = fopen("test.c", "r");
    asmfp = fopen("test.asm", "w");
    initBaseType();
    asmStartDataSegment();
    asmAddData(DWORD, "var1", 0);
    fclose(srcfp);
    fclose(asmfp);
    loggerf(INFO, "compile complete with no error(s)");
    return 0;
}