#include "scanner.h"

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

void scanSingle(Scanner *s) {
    CHECK(s);
    skipWhitespaces(s);

    Token tok;
    tok.type = TOK_ILLEGAL;
    tok.val_str = NULL;

    switch (s->cur) {
        case '+':
            tok.type = TOK_ADD;
            break;
        case '-':
            tok.type = TOK_SUB;
            break;
        case '*':
            tok.type = TOK_MUL;
            break;
        case '/':
            tok.type = TOK_DIV;
            break;
        case '%':
            tok.type = TOK_REM;
            break;
        case '(':
            tok.type = TOK_LPAREN;
            break;
        case ')':
            tok.type = TOK_RPAREN;
            break;

        case '=':
            tok.type = TOK_ASSIGN;
            break;

        case '\0':
            tok.type = TOK_EOF;
            s->done = true;
            break;

        default:
            if (isNum(s->cur)) {
                scanInt(s);
                return;
            }
            else if (isIdent(s->cur)) {
                scanIdent(s);
                return;
            }
            else {
                PANIC("illegal token");
            }
            break;
    }
    addToken(s, &tok);
}

void scanAll(Scanner *s) {
    while (!s->done) {
        scanSingle(s);
    }
}
