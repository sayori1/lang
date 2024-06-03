#ifndef UNTITLED4_TOKEN_H
#define UNTITLED4_TOKEN_H

enum TYPE {INTEGER = 0, PLUS = 1, MINUS = 2, MUL=3, DIV=4, PARB = 5, PARE = 6, END = 7};

typedef struct{
    enum TYPE type;
    void* value;
} Token;



#endif //UNTITLED4_TOKEN_H
