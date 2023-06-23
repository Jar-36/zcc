#include "util.h"
#include <string.h>


char checkLegalToken(char *token){
    char c;
    int index=0;
    while(1){
        c=token[index];
        if(c==';'||c=='('||c==' '||c==0)goto yes;
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


char getTypeToken(char *token){

}