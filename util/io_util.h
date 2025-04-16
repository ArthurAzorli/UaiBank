#ifndef IO_UTIL_H
#define IO_UTIL_H

#include "int_util.h"

/**
 * @brief: caso seja necessario, a função limpa o buffer de leitura do terminal
 * @return: valor booleano indicando se foi preciso limpar (TRUE) ou não (FALSE)
 */
bool clearBuffer();

/**
 * @brief: exibe uma menssagem formatada de erro
 * @param message: texto da mensagem exibida
 */
void error_message(char* message);

/**
 * @brief: exibe uma menssagem formatada de sucesso
 * @param message: texto da mensagem exibida
 */
void successful_message(char* message);

/**
 * @brief: espera o usuário pressionar enter
 */
void press_enter();



#endif //IO_UTIL_H
