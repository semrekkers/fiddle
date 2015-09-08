#include "parser.h"

#define NODET(e,t) case e: s = sizeof(t); break

AstNode* newNode(AstNodeType type) {
    uint s;
    switch (type) {
        NODET(NODE_IDENT, Ident);
        NODET(NODE_BASIC_LIT, BasicLit);
        NODET(NODE_UNARY_EXPR, UnaryExpr);
        NODET(NODE_BINARY_EXPR, BinaryExpr);
        NODET(NODE_PAREN_EXPR, ParenExpr);
        NODET(NODE_ASSIGN_STAT, AssignStat);

        default:
            s = sizeof(AstNode);
            break;
    }
    AstNode *n = malloc(s);
    CHECK(n);
    n->type = type;
    return n;
}

void freeNode(AstNode *node) {;
    free(node);
}

static inline Token peek(Parser *p, int i) {
    uint pos = (uint)(p->pos + i);
    return *((Token*)vec_at(&p->tokenStream, pos));
}

static void consume(Parser *p) {
    p->pos++;
    p->cur = peek(p, 0);
}

void parser_init(Parser *p, Scanner *s) {
    CHECK(p);
    CHECK(s);
    CHECK(s->tokenStream.length);
    p->pos = 0;
    p->root = NULL;
    p->tokenStream = s->tokenStream;
    p->cur = peek(p, 0);
}
