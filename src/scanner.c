#include "scanner.h"

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

static void next(Scanner *s) {
    if (s->done) {
        PANIC("illegal next");
    }
    s->cur = s->source[s->nextPos];
    s->nextPos++;
    if (s->cur == '\n') {
        s->line++;
        s->col = 0;
    }
    s->col++;
    if (s->nextPos >= s->length) {
        s->done = true;
    }
}

static void skipWhitespaces(Scanner *s) {
    while (isSpace(s->cur)) {
        next(s);
    }
}

static void addToken(Scanner *s, Token *tok) {
    vec_add(&s->tokenStream, 1, tok);
}

static void scanIdent(Scanner *s) {
    Token tok;
    tok.type = TOK_IDENT;
    tok.val_str = malloc(DEFAULT_STRLEN);
    uint i;
    for (i = 0;; i++) {
        if (!isIdent(s->cur)) {
            break;
        }
        tok.val_str[i] = s->cur;
        next(s);
    }
    tok.val_str[i] = '\0';
    addToken(s, &tok);
}

static void scanInt(Scanner *s) {
    Token tok;
    tok.type = TOK_INT;
    tok.val_int = 0;
    for (;;) {
        if (!isNum(s->cur)) {
            break;
        }
        tok.val_int *= 10;
        tok.val_int += (s->cur - '0');
        next(s);
    }
    addToken(s, &tok);
}

void scanner_init(Scanner *s, char *source, uint length) {
    CHECK(s);
    CHECK(source);
    s->cur = ' ';
    s->source = source;
    s->nextPos = 0;
    s->line = 1;
    s->col = 1;
    s->done = false;
    s->length = length;
    vec_init(&s->tokenStream, sizeof(Token), 32);
}

void scanner_free(Scanner *s) {
    CHECK(s);
    vec_free(&s->tokenStream);
}
