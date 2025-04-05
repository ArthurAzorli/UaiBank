#ifndef VECTOR_H
#define VECTOR_H
#include "../util/int_util.h"

struct vector_struct {
  void *data;
  uint64 size;
  uint32 element_size;
};

typedef struct vector_struct Vector;

bool push_back(Vector* vector, const void *value);

void *pop_back(Vector* vector);

void *remove_value(Vector* vector, const uint64 index);

uint64 search_value(const Vector* vector, const void *value);

bool contains(const Vector* vector, const void *value);

void clear(Vector* vector);


#endif //VECTOR_H
