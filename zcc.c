#include <stdio.h>
#include <stdlib.h>
#include "zcc.h"
#include "asm.h"


FILE *srcfp;
FILE *asmfp;

int main(){
    loggerf(INFO, "start compile");
    srcfp = fopen("test.c", "r");
    asmfp = fopen("test.asm", "w");
    initBaseType();
    asmStartDataSegment();
    char sent[] = "const int var_1;";
    global_var *var = getGlobalVar(sent);
    printf("%i\n", var->id);
    fclose(srcfp);
    fclose(asmfp);
    loggerf(INFO, "compile complete with no error(s)");
    return 0;
}