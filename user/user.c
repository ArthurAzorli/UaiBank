#include "user.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief: inicializa a struct User
 * @param user: ponteiro ao qual od dados serão salvaos
 * @param name: string do nome do usuario
 * @param age: idade do usuario
 */
void init_user(User *user, char *name, uint8 age) {
    if (NEXT_ID == 0) load_id();
    user->id = NEXT_ID;
    strcpy(user->name, name);
    user->age = age;
    user->balance = 0;
    NEXT_ID++;
    save_id();
}

/**
 * @brief: trata da transferecia de valor entre usuarios
 * @param sender: usuario que enviara a quantia
 * @param receiver: usuario que recebera a quantia
 * @param value: valor que será transferido
 * @return: valor booleano indicando se a transferencia foi bem sucedida
 */
bool bankTransfer(User *sender, User *receiver, double value) {

    if (!sender || !receiver) return false;
    if (sender->id == receiver->id) return false;
    if (sender->balance < value) return false;

    sender->balance -= value;
    receiver->balance += value;
    return true;
}

/**
 * @brief: carrega o ultimo id gerado
 */
void load_id() {
    FILE *file = fopen(ID_PATH, "r");
    if (!file) return;
    char line[20];
    if (fgets(line, 20, file)) {
        NEXT_ID = strtoull(line, NULL, 16);
    }
    fclose(file);
}

/**
 * @brief: salva o ultimo id gerado
 */
void save_id() {
    FILE *file = fopen(ID_PATH, "w");
    if (!file) return;
    fprintf(file, "%llx\n", NEXT_ID);
    fclose(file);
}

