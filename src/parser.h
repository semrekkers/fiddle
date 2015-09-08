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
void parser_free(Parser *p);

void parseAll(Parser *p);

#endif // FIDDLE_PARSER_H_
