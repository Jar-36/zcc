#include <stdio.h>
#include "zcc.h"
#include "asm.h"
#include "i386.h"

void compileFunction(function *func){
    asmAddFunction(func->name);
    function_init();
    function_ret();
}