#include "parser.h"

#define NODET(e,t) case e: s = sizeof(t); break
#define CUR p->cur.type

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

OpPrec getOpPrec(TokenType t) {
    // TODO: ?
    if (TOK_MUL <= t && t <= TOK_REM) {
        return 2;
    }
    else if (TOK_ADD <= t && t <= TOK_SUB) {
        return 1;
    }
}

static inline Token peek(Parser *p, int i) {
    uint pos = (uint)(p->pos + i);
    return *((Token*)vec_at(&p->tokenStream, pos));
}

static void consume(Parser *p) {
    p->pos++;
    p->cur = peek(p, 0);
}

static inline bool accept(Parser *p, TokenType t) {
    return CUR == t;
}

static void expect(Parser *p, TokenType t) {
    if (CUR != t) {
        char msg[DEFAULT_STRLEN];
        snprintf(&msg, DEFAULT_STRLEN, "expected %u, got %u", t, CUR);
        PANIC(msg);
    }
    consume(p);
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

static AstNode* parseExpr(Parser *p);
static AstNode* parseStat(Parser *p);

static Ident* parseIdent(Parser *p) {
    if (CUR != TOK_IDENT) {
        PANIC("expected an identifier");
    }
    Ident *n = (Ident*)newNode(NODE_IDENT);
    n->name = p->cur.val_str;
    consume(p);
    return n;
}

static BasicLit* parseBasicLit(Parser *p) {
    if (!isLiteral(p->cur)) {
        PANIC("expected a literal");
    }
    BasicLit *n = (BasicLit*)newNode(NODE_BASIC_LIT);
    n->tok = p->cur;
    consume(p);
    return n;
}

static UnaryExpr* parseUnaryExpr(Parser *p) {
    // the only valid unary operator is '-'
    if (CUR != TOK_SUB) {
        PANIC("expected an unary operator");
    }
    consume(p);
    AstNode *expr = parseExpr(p);
    CHECK(expr);
    UnaryExpr *n = (UnaryExpr*)newNode(NODE_UNARY_EXPR);
    n->op = CUR;
    n->right = expr;
    return n;
}

static BinaryExpr* parseBinaryExpr(Parser *p) {
    AstNode *left = parseExpr(p);
    CHECK(left);
    AstNode *right = parseExpr(p);
    CHECK(right);
    // TODO: finish it
}

static AstNode* parseAssignStat(Parser *p) {
    Ident *ident = parseIdent(p);
    expect(p, TOK_ASSIGN);
    AstNode *expr = parseExpr(p);
    CHECK(expr);
    AssignStat *n = (AssignStat*)newNode(NODE_ASSIGN_STAT);
    n->ident = ident;
    n->expr = expr;
    return (AstNode*)n;
}
