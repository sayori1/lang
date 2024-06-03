

#ifndef UNTITLED4_LEXER_H
#define UNTITLED4_LEXER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "str_utils.h"
#include "token.h"

typedef struct{
    char* text;
    int pos;
    Token current;
    char currentCh;
} Lexer;

void advance(Lexer* intr){
    intr->pos += 1;
    if(intr->pos > strlen(intr->text) - 1){
        intr->currentCh = NULL;
    }
    else{
        intr->currentCh = intr->text[intr->pos];
    }
}

void skipWhitespaces(Lexer* intr){
    while(intr->currentCh != NULL && isspace(intr->currentCh)){
        advance(intr);
    }
}

int integer(Lexer* intr){
    char* buff = "";

    while(intr->currentCh != NULL && isdigit(intr->currentCh)){
        buff = appendCharDynamic(buff,
                                 intr->currentCh);
        advance(intr);
    }

    return atoi(buff);
}

Token getNextToken(Lexer* intr){
    while(intr->currentCh != NULL){
        if(isspace(intr->currentCh)){
            skipWhitespaces(intr);
            continue;
        }

        if(isdigit(intr->currentCh)){
            int v = integer(intr);
            Token token = {INTEGER, v};
            return token;
        }
        else if(intr->currentCh == '+'){
            advance(intr);
            Token token = {PLUS, '+'};
            return token;
        }
        else if(intr->currentCh == '-'){
            advance(intr);
            Token token = {MINUS, '-'};
            return token;
        }
        else if(intr->currentCh == '*'){
            advance(intr);
            Token token = {MUL, '*'};
            return token;
        }
        else if(intr->currentCh == '/'){
            advance(intr);
            Token token = {DIV, '/'};
            return token;
        }

        else if(intr->currentCh == '('){
            advance(intr);
            Token token = {PARB, '('};
            return token;
        }

        else if(intr->currentCh == ')'){
            advance(intr);
            Token token = {PARE, ')'};
            return token;
        }

    }

    Token token = {END, NULL};
    return token;
}

void eat(Lexer* intr, enum TYPE type){
    if(intr->current.type == type){
        intr->current = getNextToken(intr);
    }
    else{
        fprintf(stderr, "Unexpected token\n");
    }
}

Lexer createLexer(char* text){
    Lexer* lexer = (Lexer*)(malloc(sizeof(Lexer)));
    lexer->text = text;

    lexer->currentCh = lexer->text[0];
    lexer->pos = 0;
    lexer->current = getNextToken(lexer);

    return *lexer;
}


#endif //UNTITLED4_LEXER_H
