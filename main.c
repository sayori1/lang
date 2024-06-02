#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "str_utils.h"


enum TYPE {INTEGER = 0, PLUS = 1, MINUS = 2, MUL=3, DIV=4, PARB = 5, PARE = 6, END = 7};

typedef struct{
    enum TYPE type;
    void* value;
} Token;

typedef struct{
    char* text;
    int pos;
    Token current;
    char currentCh;
} Interpreter;

void advance(Interpreter* intr){
    intr->pos += 1;
    if(intr->pos > strlen(intr->text) - 1){
        intr->currentCh = NULL;
    }
    else{
        intr->currentCh = intr->text[intr->pos];
    }
}

void skipWhitespaces(Interpreter* intr){
    while(intr->currentCh != NULL && isspace(intr->currentCh)){
        advance(intr);
    }
}

int integer(Interpreter* intr){
    char* buff = "";

    while(intr->currentCh != NULL && isdigit(intr->currentCh)){
        buff = appendCharDynamic(buff,
                intr->currentCh);
        advance(intr);
    }

    return atoi(buff);
}


Token getNextToken(Interpreter* intr){
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

void eat(Interpreter* intr, enum TYPE type){
    if(intr->current.type == type){
        intr->current = getNextToken(intr);
    }
    else{


        fprintf(stderr, "Unexpected token\n");
    }
}

int factor(Interpreter* intr){
    if(intr->current.type == PARB){
        eat(intr, PARB);
        int v = expr(intr);
        eat(intr, PARE);
        return v;
    }

    Token token = intr->current;
    eat(intr, INTEGER);

    return (int) token.value;
}

int term(Interpreter* intr){
    int v = factor(intr);

    while(intr->current.type == MUL || intr->current.type == DIV){
        if(intr->current.type == MUL){
            eat(intr, MUL);
            v *= factor(intr);
        }
        else if(intr->current.type == DIV){
            eat(intr, DIV);
            v /= factor(intr);
        }
    }

    return v;
}

int expr(Interpreter* intr){
    if(intr->pos == 0){
        intr->currentCh = intr->text[0];
        intr->current = getNextToken(intr);
    }


    int v = term(intr);

    while(intr->current.type == PLUS || intr->current.type == MINUS){
        if(intr->current.type == PLUS){
            eat(intr, PLUS);
            v += term(intr);
        }
        else if(intr->current.type == MINUS){
            eat(intr, MINUS);
            v -= term(intr);
        }
    }

    return v;

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
}


int main() {
    Interpreter intr = {"(2+2 - (21 * 21 + (3+4) + (5+4 + (54 + 1)))) * 2 ", 0};

    int v = expr(&intr);

    printf("%d", v);
    return 0;
}
