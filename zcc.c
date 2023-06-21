#include <stdio.h>
#include "zcc.h"


FILE *srcfp;
FILE *asmfp;



int main(){
    srcfp = fopen("test.c", "r");
    asmfp = fopen("test.asm", "w");
//    char t;
//    while (1){
//        t= fgetc(srcfp);
//        printf("%x", t);
//        if(t==EOF){
//            break;
//        }
//    }
//    printf("%s", readASen(0));
//    printf("%s", readASen(0));
//    printf("%s", readASen(0));
//    printf("%s", readASen(0));
//    printf("%s", readASen(0));
    return 0;
}