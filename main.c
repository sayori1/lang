#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "str_utils.h"


enum TYPE {INTEGER = 0, PLUS = 1, MINUS = 2, END = 3};

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
        buff = appendCharDynamic(buff, intr->currentCh);
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

        if(intr->currentCh == '+'){
            advance(intr);
            Token token = {PLUS, '+'};
            return token;
        }

        else if(intr->currentCh == '-'){
            advance(intr);
            Token token = {MINUS, '-'};
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
        _strerror("WTF");
    }
}

int expr(Interpreter* intr){
    intr->currentCh = intr->text[0];

    intr->current = getNextToken(intr);

    Token left = intr->current;
    eat(intr, INTEGER);

    Token op = intr->current;
    if(op.type == PLUS)
        eat(intr, PLUS);
    else if(op.type == MINUS)
        eat(intr, MINUS);

    Token right = intr->current;
    eat(intr, INTEGER);



    int leftV = (int)(left.value);
    int rightV = (int)(right.value);

    int result = 0;


    if(op.type == PLUS){
        result = leftV + rightV;
    }
    else{
        result = leftV - rightV;
    }

    return result;
}


int main() {
    Interpreter intr = {"  8 - 1  ", 0};

    int v = expr(&intr);

    printf("%d", v);
    return 0;
}
