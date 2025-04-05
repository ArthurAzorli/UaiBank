#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include "../vector/vector.h"
#include "../user/user.h"

static const char* FILE_PATH = "../file_save.txt";
static const char* COLUMN_DELIM = " |[&]| ";

void load_file_data(Vector*);
void create_file_data(const Vector*);
void save_user_data(const User*);

#endif //FILE_UTIL_H
