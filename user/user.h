#ifndef USER_H
#define USER_H

#include "../util/int_util.h"

static uint64 NEXT_ID = 0x0;
static const char* ID_PATH = "../id.txt";

struct user_struct {
    uint64 id;
    char name[101];
    uint8 age;
    double balance;
};
typedef struct user_struct User;

void init_user(User *user, char *name, uint8 age);

bool bankTransfer(User *sender, User *receiver, double amount);

void load_id();

void save_id();

#endif //USER_H
