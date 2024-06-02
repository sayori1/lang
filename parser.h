
#ifndef UNTITLED4_PARSER_H
#define UNTITLED4_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct{
    Lexer* lexer;
} Parser;

AST* factor(Parser* parser){
    Lexer* lexer = parser->lexer;
    if(lexer->current.type == INTEGER){
        Token token = lexer->current;
        eat(lexer, INTEGER);
        return createNum((int)token.value);
    }
}

AST* term(Parser* parser){
    Lexer* lexer = parser->lexer;

    AST* left = factor(parser);

    while(lexer->current.type == MUL || lexer->current.type == DIV){
        Token op = lexer->current;
        if(op.type == MUL){
            eat(lexer, MUL);
        }
        else if(op.type == DIV){
            eat(lexer, DIV);
        }

        return createBinOp(left, factor(parser), op.type);
    }

    return left;
}

AST* expr(Parser* parser){
    Lexer* lexer = parser->lexer;

    AST* left = term(parser);

    while(lexer->current.type == PLUS || lexer->current.type == MINUS){
        Token op = lexer->current;

        if(op.type == PLUS){
            eat(lexer, PLUS);
        }
        else if(op.type == MINUS){
            eat(lexer, MINUS);
        }
        return createBinOp(left, term(parser), op.type);
    }

    return left;
}

AST* parse(Parser* parser){
    return expr(parser);
}


#endif //UNTITLED4_PARSER_H
