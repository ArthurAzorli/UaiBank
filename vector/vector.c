#include "vector.h"

#include <stdlib.h>
#include <string.h>

bool push_back(Vector* vector, const void *value) {
 
    if (!vector) return false;

    void** newData;

    if (!vector->data) {
        newData = malloc(vector->element_size);
    } else {
        newData = realloc(vector->data, (vector->size + 1) * vector->element_size);
    }

    if (!newData) return false;

    vector->data = newData;

    void* target = (char*)vector->data + (vector->size * vector->element_size);
    memcpy(target, value, vector->element_size);

    vector->size++;

    return true;

}

void* pop_back(Vector* vector) {

    if (!vector->data || vector->size == 0) {
        return NULL;
    }

    void* oldValue = malloc(vector->element_size);
    void* newData  = realloc(vector->data, (vector->size - 1) * vector->element_size);

    if (!newData || !oldValue) {
        free(oldValue);
        free(newData);
        return NULL;
    }

    memcpy(oldValue, (char*)vector->data + (vector->size - 1) * vector->element_size, vector->element_size);

    vector->data = newData;
    vector->size--;

    return oldValue;
}

void* remove_value(Vector* vector, const uint64 index) {

    if (!vector->data || vector->size == 0 ||index >= vector->size) {
        return NULL;
    }

    void* oldValue = malloc(vector->element_size);
    void* newData  = malloc((vector->size - 1) * vector->element_size);

    if (!newData || !oldValue) {
        free(oldValue);
        free(newData);
        return NULL;
    }

    memcpy(oldValue, (char*)vector->data + index, vector->element_size);

    for (uint64 i = 0, j = 0; i < vector->size; i++) {
        if (i != index) {
            memcpy((char*)newData + j * vector->element_size, (char*)vector->data + i * vector->element_size, vector->element_size);
            j++;
        }
    }
    free(vector->data);
    vector->data = newData;
    vector->size--;

    return oldValue;

}

uint64 search_value(const Vector* vector, const void *value) {
    for (uint64 i = 0; i < vector->size; i++) {
        if (memcmp((char*)vector->data + i * vector->element_size, value, vector->element_size) == 0)
            return i;

    }
    return vector->size;
}

bool contains(const Vector* vector, const void *value) {
    for (uint64 i = 0; i < vector->size; i++) {
        if (memcmp((char*)vector->data + i * vector->element_size, value, vector->element_size) == 0)
            return true;
    }
    return false;
}

void clear(Vector *vector) {
    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
}
