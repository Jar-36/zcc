#include "zcc.h"
#include "asm.h"
#include "ctree.h"
#include "libutil/util.h"

global_var *headGlobalVar = NULL;

void readGlobalVar(){
    asmStartDataSegment();
    srcRollback();
    char *buf = NULL;
    global_var *var = NULL;
    global_var *index = headGlobalVar;
    while(1){
        buf = readASen();
        if(buf==NULL){
            break;
        }
        var = constructGlobalVar(buf);
        if(var==NULL) continue;
        asmAddData(var, 0);
        if(headGlobalVar==NULL) {
            headGlobalVar = var;
            index = headGlobalVar;
            continue;
        }
        while(1){
            if(index->next==NULL) {
                index->next = var;
                break;
            }
            index=index->next;
        }
    }
}

global_var *getGlobalVar(int id){
    if(headGlobalVar==NULL) return NULL;
    global_var *index = headGlobalVar;
    while(1){
        if(id== index->id){
            return index;
        }
        index=index->next;
        if(index==NULL){
            return NULL;
        }
    }
}
