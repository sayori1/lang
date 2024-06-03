#ifndef UNTITLED4_AST_H
#define UNTITLED4_AST_H

#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TreeType { NUM = 0, BINOP = 1, UNARYOP = 2, NONE = 3 };

typedef struct AST {
    enum TreeType type;
    char* (*toString)(struct AST* self);
} AST;

char* astToString(AST* self) {
    return "Basic AST";
}

AST* createAST() {
    AST* ast = (AST*)malloc(sizeof(AST));
    if (ast) {
        ast->type = NONE;
        ast->toString = astToString;
    }
    return ast;
}

typedef struct {
    AST base;
    int value;
} Num;

char* numToString(AST* self) {
    Num* num = (Num*)self;
    char* result = (char*)malloc(50);
    if (result) {
        snprintf(result, 50, "Num: %d", num->value);
    }
    return result;
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

typedef struct {
    AST base;
    AST* left;
    AST* right;
    enum TYPE op;
} BinOp;

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

typedef struct {
    AST base;
    Token op;
    AST* expr;
} UnaryOp;

char* unaryOpToString(AST* self) {
    UnaryOp* unaryOp = (UnaryOp*)self;
    char* exprStr = unaryOp->expr->toString(unaryOp->expr);
    char* result = (char*)malloc(strlen(exprStr) + 30);
    if (result) {
        snprintf(result, strlen(exprStr) + 30, "UnOp: (%d %s)", unaryOp->op.type, exprStr);
    }
    free(exprStr);
    return result;
}

UnaryOp* createUnaryOp(enum TYPE op, AST* expr) {
    UnaryOp* unaryOp = (UnaryOp*)malloc(sizeof(UnaryOp));
    if (unaryOp) {
        unaryOp->base.type = UNARYOP;
        unaryOp->base.toString = unaryOpToString;
        unaryOp->op.type = op;
        unaryOp->expr = expr;
    }
    return unaryOp;
}

void freeAST(AST* ast) {
    if (ast) {
        if (ast->type == BINOP) {
            BinOp* binOp = (BinOp*)ast;
            freeAST(binOp->left);
            freeAST(binOp->right);
        } else if (ast->type == UNARYOP) {
            UnaryOp* unaryOp = (UnaryOp*)ast;
            freeAST(unaryOp->expr);
        }
        free(ast);
    }
}

#endif // UNTITLED4_AST_H
