#ifndef FIDDLE_AST_H_
#define FIDDLE_AST_H_

#include "fiddle.h"
#include "scanner.h"

enum {
    NODE_INVALID = 0,

    NODE_IDENT,
    NODE_BASIC_LIT,
    NODE_UNARY_EXPR,
    NODE_BINARY_EXPR,
    NODE_PAREN_EXPR,

    NODE_ASSIGN_STAT
};

typedef uchar AstNodeType;

// base class for all ast node types
typedef struct {
    AstNodeType type;     // ast node type
} AstNode;

// ast node types

typedef struct {
    AstNode head;
    char *name;
} Ident;

typedef struct {
    AstNode head;
    Token tok;
} BasicLit;

typedef struct {
    AstNode head;
    TokenType op;
    AstNode *right;
} UnaryExpr;

typedef struct {
    AstNode head;
    AstNode *left;
    TokenType op;
    AstNode *right;
} BinaryExpr;

typedef struct {
    AstNode head;
    AstNode *inner;
} ParenExpr;

typedef struct {
    AstNode head;
    Ident *ident;
    AstNode *expr;
} AssignStat;

bool isStat(void *node);
bool isExpr(void *node);

#endif // FIDDLE_AST_H_
