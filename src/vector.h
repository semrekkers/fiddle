#ifndef FIDDLE_VECTOR_H_
#define FIDDLE_VECTOR_H_

#include "fiddle.h"

typedef struct {
    uchar *data;    // pointer to data
    uint isize;     // size of one item in bytes
    uint length;    // amount of items
} Vec;

#endif // FIDDLE_VECTOR_H_
