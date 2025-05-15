#ifndef USER_H
#define USER_H

#include "../util/int_util.h"

static uint64 NEXT_ID = 0x1;
static const char* ID_PATH = "../id.txt";

struct user_struct {
    uint64 id;
    char name[101];
    uint8 age;
    double balance;
};
typedef struct user_struct User;

/**
 * @brief: inicializa a struct User
 * @param user: ponteiro ao qual od dados serão salvaos
 * @param name: string do nome do usuario
 * @param age: idade do usuario
 */
void init_user(User *user, char *name, uint8 age);

/**
 * @brief: trata da transferecia de valor entre usuarios
 * @param sender: usuario que enviara a quantia
 * @param receiver: usuario que recebera a quantia
 * @param value: valor que será transferido
 * @return: valor booleano indicando se a transferencia foi bem sucedida
 */
bool bankTransfer(User *sender, User *receiver, const double value);

/**
 * @brief: carrega o ultimo id gerado
 */
void load_id();

/**
 * @brief: salva o ultimo id gerado
 */
void save_id();

/**
 * @brief: retorna o proximo ID
 * @return: proximo ID
 */
uint64 getNextID();

#endif //USER_H
