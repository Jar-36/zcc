#include "zcc.h"
#include "libutil/util.h"
#include <stdlib.h>
#include <string.h>

#define PREFIX_CONST 1
#define PREFIX_STATIC 2
#define PREFIX_EXTERN 3

param** processParam(char *param){
    return NULL;
}

function *constructGlobalFunction(char *sent){
    char hasRet = 0;
    char hasName = 0;
    char hasParam = 0;
    char hasPrefix = 0;
    int index = 0;
    int headIndex = 0;
    int size = 0;
    int prefix = 0;
    int getIntoParam = 0;
    int paramSize;
    function *func = (function*)malloc(sizeof(function));
    func->char_index = char_index_before_read;
    func->id = 0;
    func->isStatic = 0;
    func->isExternal = 0;
    func->name = (char*)malloc(1024);
    func->param_count = 0;
    func->param_list = (param**)malloc(sizeof(param*));
    func->return_type = 0;
    char c;
    while (1){
        c= sent[index];
        if(c==' '||c=='{'||c==';'||c=='('){
            sent[index] = 0;


            if(checkLegalToken(sent+headIndex)==LEGAL){
                if(hasName==1) loggerf(ERROR, "double define of function name");
                hasName = 1;
                func->id = hash(sent+headIndex);
                strcpy(func->name, sent+headIndex);
            }
            if(c=='('){
                processParam(sent+index);
                hasParam = 1;
                break;
            }

            size = getTypeSize(sent+headIndex);
            if(size!=0){
                if(hasRet==1) loggerf(ERROR, "double define of function return type");
                hasRet = 1;
                func->return_type = size;
            }

            prefix = checkKeyWord(sent+headIndex);
            if(prefix!=0){
                if(hasPrefix==1) loggerf(ERROR, "double define of function prefix");
                if(prefix!=13) loggerf(ERROR, "illegal prefix of function");
                hasPrefix = 1;
                func->isStatic = 1;
            }



            if(c==';'){
                func->isExternal = 0;
                break;
            }
            if(c=='{'){
                int r = 1;
                int tmp;
                while(1){
                    if(r==0){
                        fgetc(srcfp);
                        break;
                    }
                    tmp= fgetc(srcfp);
                    if(tmp=='{') r++;
                    if(tmp=='}') r--;
                }
                break;
            }
            sent[index] = c;
            headIndex = index + 1;
        }
        index++;
    }
    if(hasName==0||hasRet==0||hasParam==0) loggerf(ERROR, "illegal function define");
    return func;
}

global_var *constructGlobalVar(char *sent){
    char hasType = 0;
    char hasName = 0;
    int headIndex = 0;
    int index = 0;
    int size = 0;
    int keyword = 0;
    global_var *var = (global_var *) malloc(sizeof(global_var));
    var->flags = 0;
    var->id = 0;
    var->next = NULL;
    var->type_size = 0;
    var->name = (char*)malloc(1024);
    char c;
    while (1) {
        c = sent[index];
        if (c == ' ' || c == ';') {
            sent[index] = 0;

            if (checkLegalToken(sent + headIndex) == LEGAL) {
                if (hasName == 1) loggerf(ERROR, "double define of name type");
                hasName = 1;
                var->id = hash(sent + headIndex);
                strcpy(var->name, sent+headIndex);
            }

            keyword = checkKeyWord(sent + headIndex);
            if (keyword != 0) {
                if (keyword == 3) {
                    var->flags |= 0x1;
                }
                if (keyword == 6) {
                    if ((var->flags & (0x1 << 1)) == (0x1 << 1)) loggerf(ERROR, "conflict prefix static and extern");
                    var->flags |= (0x1 << 2);
                }
                if (keyword == 13) {
                    if ((var->flags & (0x1 << 2)) == (0x1 << 2)) loggerf(ERROR, "conflict prefix static and extern");
                    var->flags |= (0x1 << 1);
                }
            }


            size = getTypeSize(sent + headIndex);
            if (size != 0) {
                if (hasType == 1) loggerf(ERROR, "double define of var type");
                hasType = 1;
                var->type_size = size;
            }


            if (c == ';') break;
            sent[index] = c;
            headIndex = index + 1;


        }
        index++;
        if(sent[index]=='(') return NULL; // maybe a function
    }
    if (hasName == 0 || hasType == 0) loggerf(ERROR, "illegal def of var");
    return var;
}
