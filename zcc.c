#include <stdio.h>
#include "zcc.h"


FILE *srcfp;
FILE *asmfp;

void test();

int main(){
    srcfp = fopen("test.c", "r");
    asmfp = fopen("test.asm", "w");
    initBaseType();
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
//    printf("%i", checkLegalToken("hell_90o"));
//    asmStartDataSegment();
    fclose(srcfp);
    fclose(asmfp);
//    printf("%lu\n", sizeof(short));
//    printf("%lu\n", sizeof(int));
//    printf("%lu\n", sizeof(long));
//    printf("%lu\n", sizeof(float));
//    printf("%lu\n", sizeof(double));
    return 0;
}