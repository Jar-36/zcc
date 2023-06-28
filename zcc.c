#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libutil/util.h"
#include "global.h"


FILE *srcfp;
FILE *asmfp;

int main(int argc, char** argv){


    if(argc<3) loggerf(FATAL, "usage: zcc [*.c] [*.asm]");
    loggerf(INFO, "start compile");


    srcfp = fopen(argv[1], "r");
    asmfp = fopen(argv[2], "w");
    initBaseType();
    readGlobalSymbol();
    fclose(srcfp);
    fclose(asmfp);
    loggerf(INFO, "compile complete with no error(s)");
    return 0;
}
