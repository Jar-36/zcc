#include "zcc.h"
#include "libutil/util.h"
#include <stdlib.h>
#include <string.h>

#define PREFIX_CONST 1
#define PREFIX_STATIC 2
#define PREFIX_EXTERN 3

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
