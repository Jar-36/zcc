#include "zcc.h"
#include "asm.h"
#include "ctree.h"
#include "libutil/util.h"

void readGlobalSymbol(){
    char *buf = NULL;
    global_var *var = NULL;
    while(1){
        buf = readASen();
        if(buf==NULL){
            break;
        }
        var = getGlobalVar(buf);
        asmAddData(var, 0);
    }
}
