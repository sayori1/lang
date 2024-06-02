//
// Created by almetoff on 02.06.2024.
//

#ifndef UNTITLED4_INTERPRETER_H
#define UNTITLED4_INTERPRETER_H

#include "parser.h"

void *visit(AST *node);

typedef struct {
    Parser* parser;
} Interpeter;

int visitNum(AST* node){
    return ((Num*)node)->value;
}

int visitBinop(AST* node){
    BinOp* binOp = (BinOp*)node;
    if(binOp->op == MUL){
        return (int)visit(binOp->left) * (int)visit(binOp->right);
    }
    else if(binOp->op == DIV){
        return (int)visit(binOp->left) / (int)visit(binOp->right);
    }
    else if(binOp->op == PLUS){
        return (int)visit(binOp->left) + (int)visit(binOp->right);
    }
    else if(binOp->op == MINUS){
        return (int)visit(binOp->left) - (int)visit(binOp->right);
    }
}

void* visit(AST* node){
    if(node->type == BINOP){
        return visitBinop(node);
    }
    else if(node->type == NUM){
        return visitNum(node);
    }
}

int run(Interpeter* self){
    Parser* parser = self->parser;
    AST* ast = parse(parser);
    int result = visit(ast);
    return result;
}

#endif //UNTITLED4_INTERPRETER_H
