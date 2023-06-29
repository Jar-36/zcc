#include "zcc.h"
#include "asm.h"
#include "ctree.h"
#include "libutil/util.h"

global_var *headGlobalVar = NULL;
function *headFunction = NULL;

void readGlobalFunction(){
    asmStartCodeSegment();
    srcRollback();
    char *buf = NULL;
    function *func = NULL;
    function *index = headFunction;
    while(1){
        buf = readASen();
        if(buf==NULL){
            break;
        }
        func = constructGlobalFunction(buf);
        if(func==NULL) continue;
        if(func->isExternal==1) asmExternLabel(func->name);
        if(func->isStatic==0) asmGlobalLabel(func->name);
        if(headFunction==NULL){
            headFunction = func;
            index = headFunction;
            continue;
        }
        while(1){
            if(index->next==NULL){
                index->next = func;
                break;
            }
            index = index->next;
        }
    }
}

function *getFunction(int id){
    if(headFunction==NULL) return NULL;
    function *index = headFunction;
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
