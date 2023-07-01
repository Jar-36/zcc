#include "zcc.h"

local_var *headLocalVar = NULL;

int checkExprType(char *expr){
    if(strpbrk(expr, ";")==NULL) return 0;
    if(strpbrk(expr, "{")!=NULL) return EXPR_BLK;
    if(strpbrk(expr, "=")!=NULL) return EXPR_R2L;
    return EXPR_DEF;
}

void constructLocalVar(char *expr){
    char c;
    int size = 0;
    int index = 0;
    int headIndex = 0;
    int hasType = 0;
    int hasName = 0;
    int isPTR = 0;
    local_var *var = (local_var*)malloc(sizeof(local_var));
    var->PTR = 0;
    var->next = NULL;
    var->esp = currESP;
    var->id = 0;
    var->type_size = 0;
    while(1){
        c = expr[index];
        if(c==' '||c==';'||c=='*'){
            expr[index] = 0;

            size = getTypeSize(expr+headIndex);
            if(size!=0){
                if(hasType==1) loggerf(ERROR, "multiply define var type");
                hasType = 1;
                var->type_size = size;
            }

            if(checkLegalToken(expr+headIndex)==LEGAL){
                if (hasName == 1) loggerf(ERROR, "multiply define of name type");
                hasName = 1;
                var->id = hash(expr+headIndex);
            }

            if(c=='*'){
                if(isPTR >= 1) loggerf(ERROR, "illegal pointer define");
                if(hasType==1&&hasName==0){
                    var->PTR = 1;
                    isPTR = 1;
                    if(expr[index+1]=='*') {
                        var->PTR = 2;
                        index++;
                    }
                }else loggerf(ERROR, "illegal pointer define");
            }

            if (c == ';') break;
            expr[index] = c;
            headIndex = index + 1;
        }
        index++;
    }
    if (hasName == 0 || hasType == 0) loggerf(ERROR, "illegal def of var");
    if(errFlag == 1) return;
}