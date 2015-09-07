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
    union {
        char *val_str;
        int val_int;
    };
} Token;

typedef struct {
    char cur;
    char *source;
    uint nextPos;
    uint line;
    uint col;
    bool done;
    uint length;
    Vec tokenStream;
} Scanner;

void scanner_init(Scanner *s, char *source, uint length);
void scanner_free(Scanner *s);

void scanSingle(Scanner *s);
void scanAll(Scanner *s);

#endif // FIDDLE_SCANNER_H_
