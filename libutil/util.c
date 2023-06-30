#include"../zcc.h"

char errFlag = 0;



void srcRollback(){
    rewind(srcfp);
}

void asmRollback(){
    rewind(asmfp);
}

void srcSeek(int type, long offset){
    fseek(srcfp, offset, type);
}

void asmSeek(int type, long offset){
    fseek(asmfp, offset, type);
}



int hash(char *str){
    int hash = 0;
    while(*str){
        hash = (*str++) + (hash<<6) + (hash<<16) - hash;
    }
    return (hash & 0x7FFFFFFF);
}

void loggerf(int level, char *str){
    char *type="     ";
    switch (level) {
        case 1:
            type = "DEBUG";
            break;
        case 2:
            type = "INFO";
            break;
        case 3:
            type = "WARN";
            errFlag = 1;
            break;
        case 4:
            type = "ERROR";
            printf("[%li %s] %s\n", clock(), type, str);
            errFlag = 1;
            break;
        case 5:
            type = "FATAL";
            printf("[%li %s] %s\n", clock(), type, str);
            exit(-1);
    }
    printf("[%li %s] %s\n", clock(), type, str);
}


static void reverse(char s[]){
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa(int n, char s[]){
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

