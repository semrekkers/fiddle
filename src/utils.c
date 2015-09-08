#include "fiddle.h"

void _panic(const char *f, const uint l, char *msg) {
    fprintf(stderr, "[%s:%u] panic: %s\n", f, l, msg);
    fflush(stderr);
    abort();
}

void _checkFail(const char *f, const uint l, char *c) {
    fprintf(stderr, "[%s:%u] check failed: %s\n", f, l, c);
    fflush(stderr);
    abort();
}
