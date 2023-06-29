#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"../zcc.h"
#include "util.h"
type_list * headType = NULL;

int char_index_before_read = 0;

char *readASen(){
    fpos_t *pos = (fpos_t*)malloc(sizeof(fpos_t));
    fgetpos(srcfp, pos);
    char_index_before_read = pos->__pos;
    free(pos);
    int bufferCount = 0;
    int t = 0;
    char *buffer = (char*) malloc(1024*sizeof(char ));
    while (1){
        t = fgetc(srcfp);
        if (t == '{') {
            buffer[bufferCount] = t;
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
        if(t==0x0a||t=='\\') continue;
        buffer[bufferCount] = t;
        if(t==';'||t==EOF) break;
        bufferCount++;
    }
    if(bufferCount<1){
        return NULL;
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
    structure->id = hash(name);
    if(headType==NULL){
        headType = structure;
        return;
    }
    type_list *index = headType;
    while(1){
        if(index->next==NULL){
            index->next=structure;
            return;
        }
        index=index->next;
    }
}

char getTypeSize(char *name){
    if(headType==NULL){
        return 0;
    }
    type_list *index = headType;
    while(1){
        if(hash(name)== index->id){
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
    addType(-1, "void");
}

char *keywords[] = {"break", "case", "const", "continue", "else", "extern",
                    "for", "goto", "if", "register", "return", "sizeof", "static",
                    "struct", "switch", "typedef", "union", "volatile", "while"};


char checkLegalToken(char *token){
    if(checkKeyWord(token)!=0) goto no;
    if(getTypeSize(token)!=0) goto no;
    char c;
    int index=0;
    while(1){
        c=token[index];
        if(c==';'||c==' '||c==0||c=='(')goto yes;
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
        if(strcmp(token, keywords[i])==0) return i+1;
    }
    return 0;
}