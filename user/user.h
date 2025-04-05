#ifndef USER_H
#define USER_H

#include "../util/int_util.h"

struct user_struct {
    uint64 id;
    char name[101];
    uint8 age;
    double balance;
};
typedef struct user_struct User;

void user_init(User *user);

void bankTransfer(User *sender, User *receiver, double amount);

void user_free(User *user);

#endif //USER_H
