#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"../zcc.h"

type_list * head = NULL;

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

void addType(char type_size, char *name){
    type_list * structure = (type_list*) malloc(sizeof(type_list));
    structure->next = NULL;
    structure->type_size = type_size;
    structure->typestr = name;
    if(head==NULL){
        head = structure;
        return;
    }
    type_list *index = head;
    while(1){
        if(index->next==NULL){
            index->next=structure;
            return;
        }
        index=index->next;
    }
}

char getTypeSize(char *name){
    if(head==NULL){
        return 0;
    }
    type_list *index = head;
    while(1){
        if(strcmp(name, index->typestr)==0){
            return index->type_size;
        }
        index=index->next;
        if(index==NULL){
            return 0;
        }
    }
}

void initBaseType(){
    addType(BYTE, "char");
    addType(WORD, "short");
    addType(DWORD, "int");
    addType(DWORD, "long");
}