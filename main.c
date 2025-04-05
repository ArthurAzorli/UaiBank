#include <stdio.h>
#include "util/file_util.h"

int main()
{
    Vector bd = {NULL, 0 , sizeof(User)};
    User user = {0x5A, "art", 8, 109.8};
    push_back(&bd, &user);
    create_file_data(&bd);
    load_file_data(&bd);

    return 0;
}