#ifndef VECTOR_H
#define VECTOR_H
#include "../util/int_util.h"

struct vector_struct {
  void *data;
  uint64 size;
  uint32 element_size;
};

typedef struct vector_struct Vector;

/**
 * @brief: adiciona um novo valor em um vetor
 * @param vector: ponteiro do vetor ao qual o valor será adicionado
 * @param value: ponteiro do valor que será adicionado no vetor
 * @return: valor booleano indicando se adição ocorreu com sucesso (TRUE) ou não (FALSE)
 */
bool push_back(Vector* vector, const void *value);

/**
 * @brief: remove o ultimo valor de um vetor, tratando se não há valores nele
 * @param vector: ponteiro do vetor que será removido o valor
 * @return: ponteiro do valor removido
 */
void *pop_back(Vector* vector);

/**
 * @brief: remove um valor em especifico de um vetor
 * @param vector: ponteiro do valor ao qual o valor será removido
 * @param index: index ao qual o valor se encontra
 * @return: ponteiro do valor removido
 */
void *remove_value(Vector* vector, const uint64 index);

/**
 * @brief: busca por um valor em espefico dentro de um vetor
 * @param vector: ponteiro do vetor a ser vasculhado
 * @param value: ponteiro do valor a ser procurado
 * @warning: caso não haja o valor no vetor, retorna o tamanho do vetor
 * @return: index do valor
 */
uint64 search_value(const Vector* vector, const void *value);

/**
 * @brief: verifica se um determinado valor existe em um vetor
 * @param vector: ponteiro do valor a ser vasculhado
 * @param value: valor a ser ver verificado
 * @return: valor booleano indicando se o valor foi encontrado (TRUE) ou não (FALSE)
 */
bool contains(const Vector* vector, const void *value);

/**
 * @brief: limpa os dados do vetor
 * @param vector: ponteiro do vetor a ser limpo
 * @warning: não retira o valor do tamanho do elemento
 */
void clear(Vector* vector);


#endif //VECTOR_H
