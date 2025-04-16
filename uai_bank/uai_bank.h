#ifndef UAI_BANK_H
#define UAI_BANK_H

#include "../user/user.h"
#include "../vector/vector.h"

#include <stdio.h>

static Vector bd = {NULL, 0, sizeof(User)};

/**
 * @brief: carrega os dados dos usuarios do arquivo
 */
void carregar_banco();

/**
 * @brief: salva os dados dos usuarios no arquivo
 */
void salvar_banco();

/**
 * @brif: trata do cadastro de um usuario, incluindo entrada e saida
 */
void cadastrar_usuario();

/**
 * @brief: cadastra diversos usuarios de uma vez
 */
void cadastrar_multiplos_usuarios();

/**
 * @brief: delata um usuario selecionado por id
 */
void deletar_usuario();

/**
 * @brief: realiza a busca do usuario e informa seus dados
 */
void buscar_usuario();

/**
 * @brief: trata da entrada, processamento e validação do procedimento de transferencia
 */
void transferencia();

/**
 * @brief: trata da entrada, processamento e validação do procedimento de deposito
 */
void deposito();

/**
 * @brief: trata da entrada, processamento e validação do procedimento de saque
 */
void saque();

/**
 * @brief: trata da leitura de valores monetarios
 * @param title: texto a ser exibido quando solicitado o valor
 * @warning: valor maximo de leitura de 8 bytes
 * @return: valor monetario lido
 */
double ler_valor(char* title);

/**
 * @brief: trata da entrada de id, incluindo validação
 * @return: valor do id lido
 */
uint64 ler_id();

/**
 * @brief: trata da seleção do usuário, inclundo entrada e validação
 * @param title: texto a ser exibido ao solicitar a seleção
 * @return: caso não haja um erro, retorna o tamanho do vetor de usuarios;
 */
uint64 selecionar_usuario(char* title);

/**
 * @brief: verifica se existe um usuario com um id especifico
 * @param id: id do usuario a ser verificado
 * @return: valor boolean indicando se existe o usuario (TRUE) ou nao (FALSE)
 */
bool existe_usuario(const uint64 id);

/**
 * @brief: realiza o get e cast do valor de vetor de usuarios
 * @param vector: vetor de usuários
 * @param index: index a ser pego o valor
 * @return: ponteiro do valor do usuario em questão
 */
User* getUserFromVector(Vector* vector, const uint16 index);

#endif //UAI_BANK_H
