#include "int_util.h"

#include <ctype.h>

bool isNumber(const char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (!isdigit(text[i])) {
            return false;
        }
    }
    return true;
}

bool isDouble(const char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (!isdigit(text[i]) && text[i] != ',') {
            return false;
        }
    }
    return true;
}
