#include <stdio.h>
#include "zcc.h"
#include "asm.h"


FILE *srcfp;
FILE *asmfp;

int main(int argc, char** argv){
    loggerf(INFO, "start compile");
    srcfp = fopen("test.c", "r");
    asmfp = fopen("test.asm", "w");
    initBaseType();
    asmStartDataSegment();
//    char sent[] = "int i;";
//    getGlobalVar(sent);
    fclose(srcfp);
    fclose(asmfp);
    loggerf(INFO, "compile complete with no error(s)");
    return 0;
}