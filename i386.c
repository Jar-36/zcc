#include "zcc.h"

void function_init(){
    fputs("push ebp\nmov ebp, esp\n", asmfp);
}

void function_ret(){
    fputs("leave\nret\n", asmfp);
}
