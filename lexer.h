

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

//int factor(Lexer* intr){
//    if(intr->current.type == PARB){
//        eat(intr, PARB);
//        int v = expr(intr);
//        eat(intr, PARE);
//        return v;
//    }
//
//    Token token = intr->current;
//    eat(intr, INTEGER);
//
//    return (int) token.value;
//}
//
//int term(Lexer* intr){
//    int v = factor(intr);
//
//    while(intr->current.type == MUL || intr->current.type == DIV){
//        if(intr->current.type == MUL){
//            eat(intr, MUL);
//            v *= factor(intr);
//        }
//        else if(intr->current.type == DIV){
//            eat(intr, DIV);
//            v /= factor(intr);
//        }
//    }
//
//    return v;
//}
//
//int expr(Lexer* intr){
//    if(intr->pos == 0){
//        intr->currentCh = intr->text[0];
//        intr->current = getNextToken(intr);
//    }
//
//
//    int v = term(intr);
//
//    while(intr->current.type == PLUS || intr->current.type == MINUS){
//        if(intr->current.type == PLUS){
//            eat(intr, PLUS);
//            v += term(intr);
//        }
//        else if(intr->current.type == MINUS){
//            eat(intr, MINUS);
//            v -= term(intr);
//        }
//    }
//
//    return v;

//    Token left = intr->current;
//    eat(intr, INTEGER);
//
//    Token op = intr->current;
//    if(op.type == PLUS)
//        eat(intr, PLUS);
//    else if(op.type == MINUS)
//        eat(intr, MINUS);
//
//    Token right = intr->current;
//    eat(intr, INTEGER);
//
//
//
//    int leftV = (int)(left.value);
//    int rightV = (int)(right.value);
//
//    int result = 0;
//
//
//    if(op.type == PLUS){
//        result = leftV + rightV;
//    }
//    else{
//        result = leftV - rightV;
//    }
//
//    return result;
//}


#endif //UNTITLED4_LEXER_H
