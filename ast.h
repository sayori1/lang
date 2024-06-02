

#ifndef UNTITLED4_AST_H
#define UNTITLED4_AST_H

#include "token.h"

enum TreeType { NUM = 0, BINOP = 1, NONE = 2 };

typedef struct AST {
    enum TreeType type;
    char* (*toString)(struct AST* self);
} AST;

typedef struct {
    AST base;
    int value;
} Num;

typedef struct {
    AST base;
    AST* left;
    AST* right;
    enum TYPE op;
} BinOp;

char* astToString(AST* self) {
    return "Basic AST";
}

char* numToString(AST* self) {
    Num* num = (Num*)self;
    char* result = (char*)malloc(50);
    if (result) {
        snprintf(result, 50, "Num: %d", num->value);
    }
    return result;
}

char* binOpToString(AST* self) {
    BinOp* binOp = (BinOp*)self;
    char* leftStr = binOp->left->toString(binOp->left);
    char* rightStr = binOp->right->toString(binOp->right);
    char* result = (char*)malloc(strlen(leftStr) + strlen(rightStr) + 50);
    if (result) {
        snprintf(result, strlen(leftStr) + strlen(rightStr) + 50, "BinOp: (%s %d %s)", leftStr, binOp->op, rightStr);
    }
    free(leftStr);
    free(rightStr);
    return result;
}

AST* createAST() {
    AST* ast = (AST*)malloc(sizeof(AST));
    if (ast) {
        ast->type = NONE;
        ast->toString = astToString;
    }
    return ast;
}

Num* createNum(int value) {
    Num* num = (Num*)malloc(sizeof(Num));
    if (num) {
        num->base.type = NUM;
        num->base.toString = numToString;
        num->value = value;
    }
    return num;
}

BinOp* createBinOp(AST* left, AST* right, enum TYPE op) {
    BinOp* binOp = (BinOp*)malloc(sizeof(BinOp));
    if (binOp) {
        binOp->base.type = BINOP;
        binOp->base.toString = binOpToString;
        binOp->left = left;
        binOp->right = right;
        binOp->op = op;
    }
    return binOp;
}

void freeAST(AST* ast) {
    if (ast) {
        if (ast->type == BINOP) {
            BinOp* binOp = (BinOp*)ast;
            freeAST(binOp->left);
            freeAST(binOp->right);
        }
        free(ast);
    }
}

#endif //UNTITLED4_AST_H