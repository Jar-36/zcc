#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libutil/util.h"
#include "global.h"


FILE *srcfp;
FILE *asmfp;

int main(int argc, char** argv){


    //if(argc<3) loggerf(FATAL, "usage: zcc [*.c] [*.asm]");
    loggerf(INFO, "start compile");


    srcfp = fopen("test.c", "r");
    asmfp = fopen("test.asm", "w");
    initBaseType();
    readGlobalVar();
    fclose(srcfp);
    fclose(asmfp);
    loggerf(INFO, "compile complete with no error(s)");
    return 0;
}
