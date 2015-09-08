#ifndef FIDDLE_SCANNER_H_
#define FIDDLE_SCANNER_H_

#include "fiddle.h"
#include "vector.h"

enum {
    TOK_ILLEGAL = 0,
    TOK_EOF,

    TOK_IDENT,          // abc
    TOK_INT,            // 123

    TOK_ADD,            // +
    TOK_SUB,            // -
    TOK_MUL,            // *
    TOK_DIV,            // /
    TOK_REM,            // %

    TOK_LPAREN,         // (
    TOK_RPAREN,         // )

    TOK_ASSIGN          // =
};

typedef uchar TokenType;

typedef struct {
    TokenType type;
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

// helper functions
static inline bool isNum(char c) {
    return '0' <= c && c <= '9';
}

static inline bool isLower(char c) {
    return 'a' <= c && c <= 'z';
}

static inline bool isUpper(char c) {
    return 'A' <= c && c <= 'Z';
}

static inline bool isAlpha(char c) {
    return isLower(c) || isUpper(c);
}

static inline bool isAplhaNum(char c) {
    return isAlpha(c) || isNum(c);
}

static inline bool isIdent(char c) {
    return isAplhaNum(c) || c == '_';
}

static inline bool isSpace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

#endif // FIDDLE_SCANNER_H_
