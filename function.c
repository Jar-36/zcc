#include "zcc.h"



void compileFunction(function *func){
    asmAddFunction(func->name);
    function_init();
    function_ret();
}