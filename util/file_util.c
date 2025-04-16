#include "file_util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void load_file_data(Vector *vector) {
    FILE *file = fopen(FILE_DATA_PATH, "r");
    if (!file) return;

    vector->element_size = sizeof(User);

    char line[256];
    while (fgets(line, 256, file)) {

        User user;
        char* token = NULL;

        token = strtok(line, COLUMN_DELIM);
        if (token == NULL) break;
        user.id = strtoull(token, NULL, 16);

        token = strtok(NULL, COLUMN_DELIM);
        if (token == NULL) break;
        strcpy(user.name, token);

        token = strtok(NULL, COLUMN_DELIM);
        if (token == NULL) break;
        user.age = strtoul(token, NULL, 10);

        token = strtok(NULL, COLUMN_DELIM);
        if (token == NULL) break;
        user.balance = strtod(token, NULL);

        push_back(vector, &user);
    }
    fclose(file);
}

void create_file_data(const Vector *vector) {

    FILE *file = fopen(FILE_DATA_PATH, "w");
    if (!file) return;

    if (vector && vector->data) {
        for (uint64 i = 0; i < vector->size; i++) {
            User* user = &((User*)vector->data)[i];
            fprintf(file, "%llx%s%s%s%d%s%.2lf\n",
                user->id, COLUMN_DELIM, user->name,COLUMN_DELIM, user->age,COLUMN_DELIM, user->balance);
        }
    }

    fclose(file);
}

void save_user_data(const User *user) {

    FILE *file = fopen(FILE_DATA_PATH, "a");
    if (!file) return;

    fprintf(file, "%llx%s%s%s%d%s%.2lf\n",
                user->id, COLUMN_DELIM, user->name,COLUMN_DELIM, user->age,COLUMN_DELIM, user->balance);

    fclose(file);
}
