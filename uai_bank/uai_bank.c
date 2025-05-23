#include "uai_bank.h"
#include "../util/io_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/file_util.h"

void carregar_banco() {
    load_file_data(&bd);
}

void salvar_banco() {
    create_file_data(&bd);
}

void cadastrar_usuario() {

    printf("|---Cadastrar usuario---|\n\n");

    User user;

    char name[101];
    uint8 age;

    while (true) {
        printf("| Digite o nome completo do usuario: ");

        if (!scanf("%[^\n]s", name)) {
            error_message("ocorreu um erro ao ler o nome do usuario!");
            printf("Tente novamente -> ");
            continue;
        }

        if (clearBuffer()) {
            error_message("Nome excede o limite de caracteres! (100)");
            printf("Tente novamente -> ");
            continue;
        }

        name[100] = '\0';

        const uint8 size = strlen(name);
        if (size < 3) {
            error_message("Quantidade insuficiente de caracteres! Minimo 3");
            printf("Tente novamente -> ");
            continue;
        }

        name[strlen(name)] = '\0';

        break;
    }

    while (true) {
        setbuf(stdin, NULL);

        char input[4];
        printf("| Digite a idade do usuario: ");
        if (!scanf("%[^\n]s", &input)) {
            error_message("ocorreu um erro ao ler a idade do usuario!");
            printf("Tente novamente -> ");
            continue;
        }

        if (clearBuffer() || !isNumber(input)) {
            error_message("Idade invalida!");
            printf("Tente novamente -> ");
            continue;
        }

        input[3] = '\0';

        age = strtoul(input, NULL, 10);

        if (age>120 || age<0) {
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
        setbuf(stdin, NULL);
        printf("| Deseja comecar com um saldo inicial? (S/N): ");
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
        user.balance = ler_valor("Digite o valor do saldo (separado com virgula): R$ ");
    }

    setbuf(stdin, NULL);

    push_back(&bd, &user);
    save_user_data(&user);
    successful_message("Usuario criado com sucessso!");
}

void cadastrar_multiplos_usuarios() {

    printf("|---Cadastrar Multiplos Usuarios---|\n\n");

    uint8 quantity;

    while (true) {
        setbuf(stdin, NULL);
        printf("| Digite a quantidade de usuarios desejadados (Maximo 10): ");

        char input[3];
        if (!scanf("%s", &input)) {
            error_message("ocorreu um erro ao ler a quantidade de usarios");
            printf("Tente novamente -> ");
            clearBuffer();
            continue;
        }

        if (!isNumber(input)) {
            error_message("Quantidade invalida!");
            printf("Tente novamente -> ");
            continue;
        }

        quantity = strtoul(input, NULL, 10);

        if (clearBuffer()) {
            error_message("Quantidade inválida!");
            printf("Tente novamente -> ");
            continue;
        }

        if (quantity == 0) {
            error_message("Quantidade invalida!");
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
        printf("\n|----------------- Usuario %d/%d -----------------|\n\n", i+1, quantity);
        cadastrar_usuario();
    }

}

void deletar_usuario() {

    printf("|---Deletar usuario---|\n\n");

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

void buscar_usuario() {

    printf("|---Busca de Usuario---|\n\n");

    if (bd.size == 0) {
        error_message("Nao ha usuarios cadastrados!");
        return;
    }

    const uint64 index = selecionar_usuario("Selecione um Usuario");
    User* user = getUserFromVector(&bd, index);

    printf("| nome: %s \n| idade: %u \n| saldo: R$ %.2lf \n",
    user->name, user->age, user->balance);
}

void transferencia() {

    printf("|---Transferencia---|\n\n");

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

void deposito() {

    printf("|---Deposito---|\n\n");

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

void saque() {
    printf("|---Saque---|\n\n");

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

double ler_valor(char* title) {
    while (true) {

        char input[21];

        setbuf(stdin, NULL);
        printf("| %s ", title);
        if (!scanf("%[^\n]s", &input)) {
            error_message("ocorreu um erro ao ler o valor!");
            printf("Tente novamente -> ");
            continue;
        }

        if (clearBuffer() || !isDouble(input)) {
            error_message("Quantia invalida!");
            printf("Tente novamente -> ");
            continue;
        }

        const double value = strtod(input, NULL);

        if (value <= 0) {
            error_message("Quantia invalida!");
            printf("Tente novamente -> ");
            continue;
        }

        return value;
    }
}

uint64 ler_id() {
    while (true) {
        setbuf(stdin, NULL);
        printf("| Digite o ID do usuario desejado: ");

        char input[20];
        if (!scanf("%[^\n]s", input)) {
            error_message("ocorreu um erro ao ler o id!");
            printf("Tente novamente -> ");
            continue;
        }

        if (!isNumber(input)) {
            error_message("ID invalido!");
            printf("Tente novamente -> ");
            continue;
        }

        const uint64 id = strtoull(input, NULL, 10);

        if (clearBuffer()) {
            error_message("ID invalido!");
            printf("Tente novamente -> ");
            continue;
        }

        if (existe_usuario(id)) return id;

        error_message("ID invalido!");
        printf("Tente novamente -> ");
    }
}

uint64 selecionar_usuario(char* title) {

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

bool existe_usuario(const uint64 id) {
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

User* getUserFromVector(Vector* vector, const uint16 index) {
    if (!vector || !vector->data) return NULL;
    return ((User*)vector->data) + index;
}
