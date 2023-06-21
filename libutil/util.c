#include "util.h"
#include <stdlib.h>
#include <stdio.h>
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

char *readASen(_Bool rollBack){
    int bufferCount = 0;
    char t;
    char *buffer = (char*) malloc(1024*sizeof(char ));
    while (1){
        t = fgetc(srcfp);
        if(t==0x0a||t=='\\') continue;
        buffer[bufferCount] = t;
        bufferCount++;
        if(t==';'||t==EOF) break;
    }
    if(bufferCount<=1){
        buffer[0] = 0;
    }
    return buffer;
}