#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include "../vector/vector.h"
#include "../user/user.h"

static const char* FILE_DATA_PATH = "../file_save.txt";
static const char* COLUMN_DELIM = " |[&]| ";

/**
 * @brief: carrega a lista de usuarios salvos nos arquivos
 * @param vector: vetor de usuarios onde serao salvos
 */
void load_file_data(Vector* vector);

/**
 * @brief: cria/reescreve o arquivo onde serão salvos os dados dos usuarios
 * @param vector: vetor com os dados dos usuarios
 */
void create_file_data(const Vector* vector);

/**
 * @brief: adiciona uma nova linha de dados de um usuario
 * @param user: ponteiro de usuario com os dados a serem salvos
 */
void save_user_data(const User* user);


#endif //FILE_UTIL_H
