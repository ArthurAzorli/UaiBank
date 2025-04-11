#include "uai_bank.h"
#include "../util/io_util.h"
#include <stdio.h>

#include "../util/file_util.h"

void carregar_banco() {
    load_file_data(&bd);
}

void salvar_banco() {
    create_file_data(&bd);
}

/**
 * @brif: trata do cadastro de um usuario, incluindo entrada e saida
 */
void cadastrar_usuario() {

    printf("|---Cadastrar usuario---|\n");

    User user;

    char name[101];
    uint8 age;
    double balance;

    while (true) {
        printf("| Digite o nome completo do usuario: ");

        if (!fgets(name, 101, stdin)) {
            error_message("ocorreu um erro ao ler o nome do usuario!");
            printf("Tente novamente -> ");
            continue;
        }

        if (clearBuffer()) {
            error_message("Nome excede o limite de caracteres! (100)");
            printf("Tente novamente -> ");
            continue;
        }

        break;
    }

    while (true) {
        printf("Digite a idade do usuario: ");
        age = scanf("%u", &user.age);

        if (clearBuffer() ||age>120 || age<0) {
            error_message("Idade invalida!");
            printf("Tente novamente -> ");
            continue;
        }

        if (age<16) {
            error_message("Somete pessoas acima de 16 anos podem criar uma conta!");
            return;
        }
        break;
    }

    init_user(&user, name, age);

    bool init_balance = false;
    while (true) {
        printf("Deseja comecar com um saldo inicial? (S/N): ");
        const char option = (char) getchar();

        if (clearBuffer()) {
            error_message("Opcao invalida!");
            printf("Tente novamente -> ");
            continue;
        }

        switch (option) {
            case 's':
            case 'S': {
                init_balance = true;
                break;
            }
            case 'n':
            case 'N': {
                init_balance = false;
                break;
            }
            default: {
                error_message("Opcao invalida!");
                printf("Tente novamente -> ");
                continue;
            }
        }
        break;
    }

    if (init_balance) {

        while (true) {
            printf("Digite o valor do saldo: ");
            scanf("%.2ulf", &balance);

            if (clearBuffer() || 0<balance) {
                error_message("Saldo invalido!");
                printf("Tente novamente -> ");
                continue;
            }

            break;
        }
        user.balance = balance;
    }

    push_back(&bd, &user);
    save_user_data(&user);
    successful_message("Usuario criado com sucessso!");
}

void cadastrar_usuarios() {

    uint8 quantity;

    while (true) {
        printf("| Digite a quntidade de usuarios desejadados (Maximo 10): ");
        quantity = getchar();

        if (clearBuffer()) {
            error_message("Quantidade inválida!");
            printf("Tente novamente -> ");
            continue;
        }

        if (quantity>10) {
            error_message("Execedeu o limite de 10 usuarios por vez!");
            printf("Tente novamente -> ");
            continue;
        }
        break;
    }

    for (uint8 i = 0; i<quantity; i++) {
        cadastrar_usuario();
        printf("|-------------------------------------------------|\n");
    }
}

/**
 * @brief: delata um usuario selecionado por id
 * @warning: já remove o usuario do vetor de usuarios
 */
void deletar_usuario() {

    printf("\n\n |---Deletar usuario---|\n");

    if (bd.size == 0) {
        error_message("Nao ha usuarios cadastrados!");
        return;
    }

    const uint64 index = selecionar_usuario("Selecione um Usario");

    if (index != bd.size && remove_value(&bd, index)) {
        successful_message("Usuario removido com Sucesso!");
    } else {
        error_message("usuario inexistente!");
    }
    create_file_data(&bd);
}

/**
 * @brief: realiza a busca do usuario e informa seus dados
 */
void buscar_usuario() {

    printf("\n\n |---Busca de Usuario---|\n");

    if (bd.size == 0) {
        error_message("Nao ha usuarios cadastrados!");
        return;
    }

    const uint64 id = ler_id();

    for (uint64 i = 0; i < bd.size; i++) {
        const User* user = getUserFromVector(&bd, i);
        if (user->id == id) {
            printf("| nome: %s \n | idade: %u \n | saldo: %.2lf",
                user->name, user->age, user->balance);
            break;
        }
    }
}

/**
 * @brief: trata da entrada, processamento e validação do procedimento de transferencia
 */
void transferencia() {

    printf("\n\n |---Transferencia---|\n");

    if (bd.size == 0) {
        error_message("Nao ha usuarios cadastrados!");
        return;
    }

    if (bd.size < 2) {
        error_message("Nao ha usuarios o suficiente!");
        return;
    }

    const uint64 indexSender = selecionar_usuario("Selecione o Remetente");
    const uint64 indexReceiver = selecionar_usuario("Selecione o Destinatario");

    const double value = ler_valor("Digite a quantia a ser transferida: R$");

    User* sender = getUserFromVector(&bd, indexSender);
    User* receiver = getUserFromVector(&bd, indexReceiver);

    if (bankTransfer(sender, receiver, value)) {
        successful_message("Transferencia concluida com sucesso!");
    } else {
        error_message("Houve um erro durante a Transferencia!");
    }
    create_file_data(&bd);
}

/**
 * @brief: trata da entrada, processamento e validação do procedimento de deposito
 */
void deposito() {

    printf("\n\n |---Deposito---|\n");

    if (bd.size == 0) {
        error_message("Nao ha usuarios cadastrados!");
        return;
    }

    const uint64 index = selecionar_usuario("Selecione um Usuario");
    User* user = getUserFromVector(&bd, index);

    const double value = ler_valor("Digite a quantia a ser depositada: R$");

    user->balance += value;
    successful_message("Deposito realizado com sucesso!");
    create_file_data(&bd);
}

/**
 * @brief: trata da entrada, processamento e validação do procedimento de saque
 */
void saque() {
    printf("\n\n |---Saque---|\n");

    if (bd.size == 0) {
        error_message("Nao ha usuarios cadastrados!");
        return;
    }

    const uint64 index = selecionar_usuario("Selecione um Usuario");
    User* user = getUserFromVector(&bd, index);

    const double value = ler_valor("Digite a quantia a ser depositada: R$");

    if (value > user->balance) {
        error_message("Valor de saque é suparior ao saldo disponivel!");
    }
    else {
        successful_message("Saldo realizado com sucesso!");
        user->balance -= value;
    }
    create_file_data(&bd);
}

/**
 * @brief: trata da leitura de valores monetarios
 * @param title: texto a ser exibido quando solicitado o valor
 * @return: valor monetario lido
 */
double ler_valor(char* title) {
    double value;
    while (true) {

        printf("| %s ", title);
        scanf("%.2lf", &value);

        if (clearBuffer() || value <= 0) {
            error_message("Quantia invalida!");
            printf("Tente novamente -> ");
            continue;
        }

        return value;
    }
}

/**
 * @brief: trata da entrada de id, incluindo validação
 * @return: valor do id lido
 */
uint64 ler_id() {
    uint64 id;
    while (true) {
        printf("| Digite o ID do usuario desejado: ");
        scanf("%llu", &id);

        if (clearBuffer() || NEXT_ID<id) {
            error_message("ID invalido!");
            printf("Tente novamente -> ");
            continue;
        }

        if (existe_usuario(id)) return id;

        error_message("ID invalido!");
        printf("Tente novamente -> ");
    }
}

/**
 * @brief: trata da seleção do usuário, inclundo entrada e validação
 * @param title: texto a ser exibido ao solicitar a seleção
 * @return: caso não haja um erro, retorna o tamanho do vetor de usuarios;
 */
uint64 selecionar_usuario(char* title) {
    //load_file_data(&bd);
    if (bd.size == 0) {
        error_message("Nao ha usuarios cadastrados!");
        return bd.size;
    }

    printf("\n\n|--- %s ---|\n|\n", title);
    for (uint64 i = 0; i < bd.size; i++) {
        const User *user = getUserFromVector(&bd, i);
        printf("| [%lld] %s \n", user->id, user->name);
    }
    printf("| \n");

    const uint64 id = ler_id();

    for (uint64 i = 0; i < bd.size; i++) {
        const User *user = getUserFromVector(&bd, i);
        if (user && user->id == id) {
            return i;
        }
    }
    return bd.size;
}

/**
 * @brief: verifica se existe um usuario com um id especifico
 * @param id: id do usuario a ser verificado
 * @return: valor boolean indicando se existe o usuario (TRUE) ou nao (FALSE)
 */
bool existe_usuario(uint64 id) {
    bool exist = false;
    for (uint64 i = 0; i < bd.size; i++) {
        const User *user = getUserFromVector(&bd, i);
        if (user && user->id == id) {
            exist = true;
            break;
        }
    }
    return exist;
}

/**
 * @brief: realiza o get e cast do valor de vetor de usuarios
 * @param vector: vetor de usuários
 * @param index: index a ser pego o valor
 * @return: ponteiro do valor do usuario em questão
 */
User* getUserFromVector(Vector* vector, uint16 index) {
    if (!vector || !vector->data) return NULL;
    return ((User*)vector->data) + index;
}
