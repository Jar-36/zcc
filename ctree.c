#include "zcc.h"

#define PREFIX_CONST 1
#define PREFIX_STATIC 2
#define PREFIX_EXTERN 3

void processParam(char *p, function *func) {
    if(p[0]==' '||p[0]==0) return;
    int index = 1;
    int headIndex = 1;
    int size = 0;
    int status = 1;
    char c;
    param *pIndex = NULL;
    while (1) {
        c = p[index];

        if (c == ')' || c == ' ' || c == ','||c=='*') {
            p[index] = 0;
            size = getTypeSize(p + headIndex);
            if (size != 0) {
                func->param_count++;
                if (status == 2) loggerf(ERROR, "illegal define of function parameters type");
                if (func->param_list_head == NULL) {
                    func->param_list_head = (param *) malloc(sizeof(param));
                    pIndex = func->param_list_head;
                    goto con;
                }
                pIndex->next = (param *) malloc(sizeof(param));
                pIndex = pIndex->next;
                con:
                pIndex->type = size;
                pIndex->next = NULL;
                status = 2;
            }
            if (checkLegalToken(p + headIndex) == LEGAL) {
                if (status == 1) loggerf(ERROR, "illegal define of function parameters name");
                pIndex->id = hash(p + headIndex);
            }
            if(c=='*'){
                if(status==1){
                    pIndex->PTR = 1;
                    if(p[index+1]=='*') {
                        pIndex->PTR = 2;
                        index++;
                    }
                }else loggerf(ERROR, "illegal pointer define");
            }
            if (c == ')') break;
            if (c == ',') status = 1;
            p[index] = c;
            headIndex = index + 1;
        }
        index++;
    }
}

function *constructGlobalFunction(char *sent) {
    errFlag = 0;
    char hasRet = 0;
    char hasName = 0;
    char hasParam = 0;
    char hasPrefix = 0;
    int index = 0;
    int headIndex = 0;
    int size = 0;
    int prefix = 0;
    int isPTR = 0;
    function *func = (function *) malloc(sizeof(function));
    func->char_index = char_index_before_read;
    func->id = 0;
    func->isStatic = 0;
    func->isExternal = 0;
    func->name = (char *) malloc(1024);
    func->param_count = 0;
    func->param_list_head = NULL;
    func->return_type = 0;
    char c;
    while (1) {
        c = sent[index];

        if (c == ' ' || c == '{' || c == ';' || c == '('||c=='*') {
            sent[index] = 0;


            if (checkLegalToken(sent + headIndex) == LEGAL) {
                if (hasName == 1) loggerf(ERROR, "double define of function name");
                hasName = 1;
                func->id = hash(sent + headIndex);
                strcpy(func->name, sent + headIndex);
            }
            if (c == '(') {
                processParam(sent + index, func);
                hasParam = 1;
                break;
            }

            size = getTypeSize(sent + headIndex);
            if (size != 0) {
                if (hasRet == 1) loggerf(ERROR, "double define of function return type");
                hasRet = 1;
                func->return_type = size;
            }

            prefix = checkKeyWord(sent + headIndex);
            if (prefix != 0) {
                if (hasPrefix == 1) loggerf(ERROR, "double define of function prefix");
                if (prefix != 13) loggerf(ERROR, "illegal prefix of function");
                hasPrefix = 1;
                func->isStatic = 1;
            }

            if(c=='*'){
                if(isPTR >= 1) loggerf(ERROR, "illegal pointer define");
                if(hasRet==1&&hasName==0){
                    func->retPTR=1;
                    isPTR = 1;
                    if(sent[index+1]=='*') {
                        func->retPTR=2;
                        index++;
                    }
                }else loggerf(ERROR, "illegal pointer define");
            }


            if (c == ';') {
                func->isExternal = 0;
                break;
            }
            if (c == '{') {
                int r = 1;
                int tmp;
                while (1) {
                    if (r == 0) {
                        fgetc(srcfp);
                        break;
                    }
                    tmp = fgetc(srcfp);
                    if (tmp == '{') r++;
                    if (tmp == '}') r--;
                }
                break;
            }
            sent[index] = c;
            headIndex = index + 1;
        }
        index++;
    }
    if (hasName == 0 || hasRet == 0 || hasParam == 0) errFlag = 1;
    if(errFlag == 1) return NULL;
    return func;
}

global_var *constructGlobalVar(char *sent) {
    if(strpbrk(sent, "{")!=NULL) return NULL;
    errFlag = 0;
    char hasType = 0;
    char hasName = 0;
    int headIndex = 0;
    int index = 0;
    int size = 0;
    int keyword = 0;
    int isPTR = 0;
    global_var *var = (global_var *) malloc(sizeof(global_var));
    var->flags = 0;
    var->id = 0;
    var->next = NULL;
    var->type_size = 0;
    var->name = (char *) malloc(1024);
    char c;
    while (1) {
        c = sent[index];

        if (c == ' ' || c == ';'||c=='*') {
            sent[index] = 0;

            if (checkLegalToken(sent + headIndex) == LEGAL) {
                if (hasName == 1) loggerf(ERROR, "double define of name type");
                hasName = 1;
                var->id = hash(sent + headIndex);
                strcpy(var->name, sent + headIndex);
            }

            keyword = checkKeyWord(sent + headIndex);
            if (keyword != 0) {
                if (keyword == 3) {
                    var->flags |= 0x1;
                }
                if (keyword == 6) {
                    if ((var->flags & (0x1 << 1)) == (0x1 << 1))
                        loggerf(ERROR, "conflict prefix static and extern");
                    var->flags |= (0x1 << 2);
                }
                if (keyword == 13) {
                    if ((var->flags & (0x1 << 2)) == (0x1 << 2))
                        loggerf(ERROR, "conflict prefix static and extern");
                    var->flags |= (0x1 << 1);
                }
            }


            size = getTypeSize(sent + headIndex);
            if (size != 0) {
                if (hasType == 1) loggerf(ERROR, "double define of var type");
                hasType = 1;
                var->type_size = size;
            }

            if(c=='*'){
                if(isPTR >= 1) loggerf(ERROR, "illegal pointer define");
                if(hasType==1&&hasName==0){
                    var->flags&=(0x1<<3);
                    isPTR = 1;
                    if(sent[index+1]=='*') {
                        var->flags&=(0x1<<4);
                        index++;
                    }
                }else loggerf(ERROR, "illegal pointer define");
            }


            if (c == ';') break;
            sent[index] = c;
            headIndex = index + 1;


        }
        index++;
        if (sent[index] == '(') loggerf(ERROR, "not a var"); // maybe a function
    }
    if (hasName == 0 || hasType == 0) loggerf(ERROR, "illegal def of var");
    if(errFlag == 1) return NULL;
    return var;
}
