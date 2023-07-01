#include "zcc.h"

int currESP = 0;

void compileFunction(function *func){
    if(func->id==hash("main")){
        asmGlobalLabel("_start");
        asmAddFunction("_start");
    } else{
        asmGlobalLabel(func->name);
        asmAddFunction(func->name);
    }

    function_init();
    if(func->id!=hash("main")){
        function_ret();
    } else{
        all_ret();
    }
}