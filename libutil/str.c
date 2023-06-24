#include "util.h"
#include <string.h>

char *keywords[] = {"break", "case", "const", "continue", "else", "extern",
                    "for", "goto", "if", "register", "return", "sizeof", "static",
                    "struct", "switch", "typedef", "union", "volatile", "while"};


char checkLegalToken(char *token){
    if(getTypeSize(token)!=0) goto no;
    if(checkKeyWord(token)==1) goto no;
    char c;
    int index=0;
    while(1){
        c=token[index];
        if(c==';'||c=='('||c==' '||c==0)goto yes;
        if(c=='_') {
            if(index==0) goto no;
            else goto con;
        }
        if(c<'0') goto no;
        if(c>'9'&&c<'A') goto no;
        if(c>'Z'&&c<'a') goto no;
        if(c>'z') goto no;
        con:
        index++;
    }
    no:
    return 0;
    yes:
    return 1;
}

char checkKeyWord(char *token){
    for(int i=0;i<19;i++){
        if(strcmp(token, keywords[i])==0) goto yes;
    }
    goto no;
    no:
    return 0;
    yes:
    return 1;
}