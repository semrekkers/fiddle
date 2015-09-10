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

static inline Token peek(Parser *p, int i) {
    uint pos = (uint)(p->pos + i);
    return *((Token*)vec_at(&p->tokenStream, pos));
}

static void consume(Parser *p) {
    p->pos++;
    p->cur = peek(p, 0);
}

static void setPosTo(Parser *p, int i) {
    p->cur = peek(p, i);
    p->pos += i;
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

static AstNode* parseIdent(Parser *p) {
    if (CUR != TOK_IDENT) {
        return NULL;
    }
    Ident *n = (Ident*)newNode(NODE_IDENT);
    n->name = p->cur.val_str;
    consume(p);
    return (AstNode*)n;
}

static AstNode* parseBasicLit(Parser *p) {
    if (!isLiteral(p->cur)) {
        return NULL;
    }
    BasicLit *n = (BasicLit*)newNode(NODE_BASIC_LIT);
    n->tok = p->cur;
    consume(p);
    return (AstNode*)n;
}

static bool isUnaryOp(Token tok) {
    switch (tok.type) {
        case TOK_ADD:
        case TOK_SUB:
            return true;
        
        default:
            return false;
    }
}

static AstNode* parseUnaryExpr(Parser *p) {
    if (!isUnaryOp(p->cur)) {
        return NULL;
    }
    TokenType op = CUR;
    consume(p);
    AstNode *expr = parseExpr(p);
    if (!expr) {
        setPosTo(p, -1);
        return NULL;
    }
    UnaryExpr *n = (UnaryExpr*)newNode(NODE_UNARY_EXPR);
    n->op = op;
    n->right = expr;
    return (AstNode*)n;
}

static int getOpPrec(Token tok) {
    switch (tok.type) {
        case TOK_ADD:
        case TOK_SUB:
            return 1;
            
        case TOK_MUL:
        case TOK_DIV:
        case TOK_REM:
            return 2;
        
        default:
            return 0;
    }
}