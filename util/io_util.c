#include "io_util.h"
#include <stdio.h>

/**
 * @brief: caso seja necessario, a função limpa o buffer de leitura do terminal
 * @return: valor booleano indicando se foi preciso limpar (TRUE) ou não (FALSE)
 */
bool clearBuffer() {
    int c;
    bool result = false;
    while ((c = getchar()) != '\n' && c != EOF) {
        result = true;
    }
    return result;
}

/**
 * @brief: exibe uma menssagem formatada de erro
 * @param message: texto da mensagem exibida
 */
void error_message(char *message) {
    printf("\x1b[31mErro: %s\n\e[0;37m", message);
}

/**
 * @brief: exibe uma menssagem formatada de sucesso
 * @param message: texto da mensagem exibida
 */
void successful_message(char *message) {
    printf("\x1b[0;32m%s\n\e[0;37m", message);
}

/**
 * @brief: espera o usuário pressionar enter
 */
void press_enter() {
    printf("Pressione Enter para continuar...");
    clearBuffer();
}
