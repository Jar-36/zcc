#include "zcc.h"

char asmStatusFlags = 0x0;
// status flags
//   high<<<<<bit                                                                            bit>>>>>low
//    b7     |    b6    |    b5    |     b4    |       b3     |       b2     |      b1        |     b0
//  reserved | reserved | reserved | reserved  | now in .data | now in .text | now in .rodata | reserved

void asmStartDataSegment(){
    if((asmStatusFlags&(0x1<<3))==(0x1<<3)) return;
    fputs("SECTION .data\n", asmfp);
    asmStatusFlags|=(0x1<<3);
}

void asmStartCodeSegment(){
    if((asmStatusFlags&(0x1<<2))==(0x1<<2)) return;
    fputs("SECTION .text\n", asmfp);
    asmStatusFlags|=(0x1<<2);
}

void asmStartRodataSegment(){
    if((asmStatusFlags&(0x1<<1))==(0x1<<1)) return;
    fputs("SECTION .rodata\n", asmfp);
    asmStatusFlags|=(0x1<<1);
}

void asmGlobalLabel(char *label){
    char *dst = (char*)malloc(1024);
    sprintf(dst, "GLOBAL %s\n", label);
    fputs(dst, asmfp);
    free(dst);
}

void asmExternLabel(char *label){
    char *dst = (char*)malloc(1024);
    sprintf(dst, "EXTERN %s\n", label);
    fputs(dst, asmfp);
    free(dst);
}

void asmAddFunction(char *label){
    char *dst = (char*)malloc(1024);
    sprintf(dst,"%s:\n", label);
    fputs(dst, asmfp);
    free(dst);
}

void asmAddData(global_var* var, long data){
    int ro = 0;
    if((asmStatusFlags&(0x1<<3))!=(0x1<<3)){
        if((asmStatusFlags&(0x1<<1))!=(0x1<<1)) loggerf(ERROR, "internal error");
    }
    if((var->flags&(0x1<<2))==(0x1<<2)){
        asmExternLabel(var->name);
        goto ext;
    }
    if((var->flags&(0x1))==0x1) {
        asmStartRodataSegment();
        ro = 1;
        asmStatusFlags&=(0x1<<1);
    }
    if((var->flags&(0x1<<1))!=(0x1<<1)){
        asmGlobalLabel(var->name);
    }
    char *len="db";
    char *buffer = (char*)malloc(16);
    switch (var->type_size) {
        case BYTE:
            if(data>0xff) loggerf(ERROR, "\'char\' type var is bigger than 0xff");
            sprintf(buffer, "%ld", data);
            break;
        case WORD:
            if(data>0xffff) loggerf(ERROR, "\'short\' type var is bigger than 0xffff");
            len="dw";
            sprintf(buffer, "%ld", data);
            break;
        case DWORD:
            if(data>0xffffffff) loggerf(ERROR, "\'int\' type var is bigger than 0xffffffff");
            sprintf(buffer, "%ld", data);
            len="dd";
            break;
    }
    char *dst = (char*)malloc(1024);
    sprintf(dst, "%s: %s %s\n", var->name, len, buffer);
    fputs(dst, asmfp);
    free(buffer);
    free(dst);
    ext:
    if(ro==1) asmStartDataSegment();
}
