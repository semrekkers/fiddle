#ifndef FIDDLE_VECTOR_H_
#define FIDDLE_VECTOR_H_

#include "fiddle.h"

typedef struct {
    uchar *data;    // pointer to data
    uint isize;     // size of one item in bytes
    uint length;    // amount of items
    uint cap;       // vector capacity
} Vec;

void vec_init(Vec *v, uint itemSize, uint len);
void vec_destroy(Vec *v);

void vec_add(Vec *v, uint count, void *data);
void* vec_at(Vec *v, uint i);

#endif // FIDDLE_VECTOR_H_
