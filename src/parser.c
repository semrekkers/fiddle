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
