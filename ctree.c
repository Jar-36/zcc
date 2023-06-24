#include "zcc.h"
#include <stdlib.h>
#include <string.h>

global_var *getGlobalVar(char *sent){
    int srcindex = 0;
    int bufindex = 0;
    char *buffer=(char*)malloc(1024);
    char c;
    global_var *var=(global_var*)malloc(sizeof(global_var));
    var->flags = 0;
    var->value = 0;
    var->name = NULL;
    var->type_size = 0;
    while(1){
        c=sent[srcindex];
        if(c==' '||c==';'){
            bufindex++;
            buffer[bufindex-1] = 0;
            if(getTypeSize(buffer)!=0) {
                if(var->type_size!=0) loggerf(ERROR, "double define of type");
                var->type_size=getTypeSize(buffer);
                goto out;
            }
            if(checkLegalToken(buffer)==1){
                if(var->name!=NULL) loggerf(ERROR, "double define of var name");
                char *token = (char*)malloc(bufindex);
                strcpy(token, buffer);
                var->name = token;
                goto out;
            }
            if(checkKeyWord(buffer)==1){
                if(strcmp(buffer, "const")==0) var->flags|=(0x1);
                if(strcmp(buffer, "static")==0) var->flags|=(0x1<<1);
                if(strcmp(buffer, "extern")==0) var->flags|=(0x1<<2);
                goto out;
            }
            loggerf(ERROR, "Illegal token error");
            out:
                bufindex = 0;
                srcindex++;
                if(c==';') break;
                continue;
        }
        buffer[bufindex] = c;
        bufindex++;
        srcindex++;
    }
    return var;
}