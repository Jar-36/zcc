#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include"../zcc.h"



void srcRollback(){
    rewind(srcfp);
}

void asmRollback(){
    rewind(asmfp);
}

void srcSeek(int type, long offset){
    fseek(srcfp, offset, type);
}

void asmSeek(int type, long offset){
    fseek(asmfp, offset, type);
}



unsigned int hash(char *str){
    unsigned int hash = 0;
    while(*str){
        hash = (*str++) + (hash<<6) + (hash<<16) - hash;
    }
    return (hash & 0x7FFFFFFF);
}

void loggerf(int level, char *str){
    char *type="     ";
    switch (level) {
        case 1:
            type = "DEBUG";
            break;
        case 2:
            type = "INFO";
            break;
        case 3:
            type = "WARN";
            break;
        case 4:
            type = "ERROR";
            printf("[%li %s] %s\n", clock(), type, str);
            remove("test.asm");
            exit(-1);
        case 5:
            type = "FATAL";
            printf("[%li %s] %s\n", clock(), type, str);
            remove("test.asm");
            exit(-1);
    }
    printf("[%li %s] %s\n", clock(), type, str);
}

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