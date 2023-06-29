#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libutil/util.h"
#include "global.h"
#include "ctree.h"


FILE *srcfp;
FILE *asmfp;

int main(int argc, char** argv){


    // if(argc<3) loggerf(FATAL, "usage: zcc [*.c] [*.asm]");
    loggerf(INFO, "start compile");


    srcfp = fopen("test.c", "r");
    asmfp = fopen("test.asm", "w");
    initBaseType();

    readGlobalVar();
    readGlobalFunction();

    // printf("%i %i %i %s %i %i\n", func->param_count, func->id, func->isExternal, func->name, func->isStatic, func->return_type);
    // printf("%x %x %i %i %i %i %x\n", func->param_list_head, func->param_list_head->next, func->param_list_head->id, func->param_list_head->type, func->param_list_head->next->id, func->param_list_head->next->type, func->param_list_head->next->next);
    fclose(srcfp);
    fclose(asmfp);
    loggerf(INFO, "compile complete with no error(s)");
    return 0;
}
