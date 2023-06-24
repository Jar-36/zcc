#include "../zcc.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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
            break;
        case 4:
            type = "ERROR";
            printf("[%li %s] %s\n", clock(), type, str);
            remove("test.asm");
            exit(-1);
        case 5:
            type = "FATAL";
            printf("[%li %s] %s\n", clock(), type, str);
            remove("test.asm");
            exit(-1);
    }
    printf("[%li %s] %s\n", clock(), type, str);
}