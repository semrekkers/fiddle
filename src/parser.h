#ifndef FIDDLE_PARSER_H_
#define FIDDLE_PARSER_H_

#include "fiddle.h"
#include "vector.h"
#include "scanner.h"
#include "ast.h"

typedef struct {
    Token cur;
    uint pos;
    AstNode *root;
    Vec tokenStream;
} Parser;

AstNode* newNode(AstNodeType type);
void freeNode(AstNode *node);

void parser_init(Parser *p, Scanner *s);

// placeholder
#define parser_free(p)

void parseAll(Parser *p);

#endif // FIDDLE_PARSER_H_
