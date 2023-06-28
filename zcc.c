#include <stdio.h>
#include "libutil/util.h"
#include "global.h"


FILE *srcfp;
FILE *asmfp;

int main(){
    loggerf(INFO, "start compile");
    srcfp = fopen("test.c", "r");
    asmfp = fopen("test.asm", "w");
    initBaseType();
    readGlobalSymbol();
    fclose(srcfp);
    fclose(asmfp);
    loggerf(INFO, "compile complete with no error(s)");
    return 0;
}
