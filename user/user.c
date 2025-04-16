#include "user.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_user(User *user, char *name, uint8 age) {
    if (NEXT_ID == 0) load_id();
    user->id = NEXT_ID;
    strcpy(user->name, name);
    user->age = age;
    user->balance = 0;
    NEXT_ID++;
    save_id();
}

bool bankTransfer(User *sender, User *receiver, const double value) {

    if (!sender || !receiver) return false;
    if (sender->id == receiver->id) return false;
    if (sender->balance < value) return false;

    sender->balance -= value;
    receiver->balance += value;
    return true;
}

void load_id() {
    FILE *file = fopen(ID_PATH, "r");
    if (!file) return;
    char line[20];
    if (fgets(line, 20, file)) {
        NEXT_ID = strtoull(line, NULL, 16);
    }
    fclose(file);
}

void save_id() {
    FILE *file = fopen(ID_PATH, "w");
    if (!file) return;
    fprintf(file, "%llx\n", NEXT_ID);
    fclose(file);
}

uint64 getNextID() {
    return NEXT_ID;
}