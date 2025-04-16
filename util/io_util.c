#include "io_util.h"
#include <stdio.h>

bool clearBuffer() {
    int c;
    bool result = false;
    while ((c = getchar()) != '\n' && c != EOF) {
        result = true;
    }
    return result;
}

void error_message(char *message) {
    printf("\x1b[31mErro: %s\n\e[0;37m", message);
}

void successful_message(char *message) {
    printf("\x1b[0;32m%s\n\e[0;37m", message);
}

void press_enter() {
    printf("Pressione Enter para continuar...");
    clearBuffer();
}
