#include "zcc.h"
#include <stdio.h>
#include <stdlib.h>

char asmStatusFlags = 0x0;
// status flags
//   high<<<<<bit                                                                                        bit>>>>>low
//    b7         |       b6     |        b5      |     b4    |       b3     |       b2     |      b1        |     b0
//  inited .data | inited .text | inited .rodata | reserved  | now in .data | now in .text | now in .rodata | reserved

void asmStartDataSegment(){
    if((asmStatusFlags&(0x1<<3))==(0x1<<3)) return;
    fputs("SECTION .data\n", asmfp);
    asmStatusFlags|=(0x1<<3);
    asmStatusFlags|=(0x1<<7);
}

void asmAddData(char size, char *label, long data){
    if((asmStatusFlags&(0x1<<3))!=(0x1<<3)) loggerf(ERROR, "cannot construct data segment (this is a internal error)");
    char *len="db";
    char *buffer = (char*)malloc(16);
    switch (size) {
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
    sprintf(dst, "%s: %s %s\n", label, len, buffer);
    fputs(dst, asmfp);
}