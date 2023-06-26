#include "zcc.h"
#include <stdlib.h>
#include <string.h>

global_var *getGlobalVar(char *sent){
   char hasPrefix = 0;
   char hasType = 0;
   char hasName = 0;
   int headIndex = 0;
   int index = 0;
   int size = 0;
   global_var *var = (global_var*)malloc(sizeof(global_var));
   var->flags = 0;
   var->name = NULL;
   var->next = NULL;
   var->type_size = 0;
   char c;
   while(1){
       c = sent[index];
       if(c==';') break;
       if(c==' '){
           sent[index] = 0;
           printf("reach target %s\n", sent+headIndex);
           size = getTypeSize(sent+headIndex);
           if(size!=0){
               printf("%i is type size\n", size);
               if(hasType==1) loggerf(ERROR, "double define of var type");
               hasType = 1;
               var->type_size = size;
           }
           sent[index] = c;
           headIndex = index+1;
       }
       index++;
   }
    return var;
}