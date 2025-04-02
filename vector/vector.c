#include "vector.h"

#include <stdlib.h>
#include <string.h>

bool push_back(Vector* vector, void *value) {

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

void * pop_back(Vector* vector) {

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

void * remove_value(Vector* vector, uint64 index) {

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

/*
int testVector() {

    Vector vector = {NULL, 0, sizeof(uint16)};

    uint16 value1 = 10;
    uint16 value2 = 20;
    uint16 value3 = 30;
    uint16 value4 = 40;

    if (push_back(&vector, &value1)) printf("valor 1 adicionado com sucesso!\n");
    if (push_back(&vector, &value2)) printf("valor 2 adicionado com sucesso!\n");
    if (push_back(&vector, &value3)) printf("valor 3 adicionado com sucesso!\n");

    for (uint64 i = 0; i < vector.size; i++) {
        uint16 value = *((uint16*)(vector.data) + i);
        printf("O valor no indice %llu eh: %d\n", i, value);
    }

    uint16 valorRemovido = *(uint16*) pop_back(&vector);
    printf("O valor removido eh: %d\n", valorRemovido);

    for (uint64 i = 0; i < vector.size; i++) {
        uint16 value = *((uint16*)(vector.data) + i);
        printf("O valor no indice %llu eh: %d\n", i, value);
    }

    printf("Tem o valor 20? %d \n", contains(&vector, &value2));
    printf("Tem o valor 30? %d \n", contains(&vector, &value3));

    printf("Onde esta o valor 20? %lld \n", search_value(&vector, &value2));
    printf("Onde esta o valor 40? %lld \n", search_value(&vector, &value4));

    uint16 valorRemovido1 = *(uint16*) remove_value(&vector, 0);
    printf("O valor removido no index 0 eh: %d\n", valorRemovido1);

    for (uint64 i = 0; i < vector.size; i++) {
        uint16 value = *((uint16*)(vector.data) + i);
        printf("O valor no indice %llu eh: %d\n", i, value);
    }

    clear(&vector);

    return 0;
}
 */
