#include "vector.h"

#define AT(v,i) (v->data + (v->isize * (i)))

static inline void expand(Vec *v, uint req) {
    uint need = v->length + req;
    if (need > v->cap) {
        uint nsize = v->cap;
        do {
            nsize <<= 1;
        } while (need > nsize);
        void *nptr = realloc(v->data, nsize * v->isize);
        CHECK(nptr);
        v->data = nptr;
        v->cap = nsize;
    }
}

void vec_init(Vec *v, uint itemSize, uint cap) {
    CHECK(v);
    uint t = itemSize * cap;
    v->data = malloc(t);
    CHECK(v->data);
    v->isize = itemSize;
    v->length = 0;
    v->cap = cap;
}

void vec_free(Vec *v) {
    CHECK(v);
    free(v->data);
}

void vec_add(Vec *v, uint count, void *data) {
    CHECK(v);
    CHECK(data);
    expand(v, count);
    uint t = v->isize * count;
    memcpy(AT(v, v->length), data, t);
    v->length += count;
}

void* vec_at(Vec *v, uint i) {
    CHECK(v);
    if (i >= v->length)
        return NULL;
    return AT(v, i);
}
