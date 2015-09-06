#ifndef FIDDLE_SCANNER_H_
#define FIDDLE_SCANNER_H_

#include "fiddle.h"

typedef enum {
    TOK_ILLEGAL = 0,
    TOK_EOF,

    TOK_IDENT,          // abc
    TOK_INT,            // 123

    TOK_ADD,            // +
    TOK_SUB,            // -
    TOK_MUL,            // *
    TOK_DIV,            // /
    TOK_REM,            // %

    TOK_ASSIGN          // =
} TokenType;

typedef struct {
    uchar type;
    char *value
} Token;

#endif // FIDDLE_SCANNER_H_
