#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "str_utils.h"
#include "lexer.h"
#include "ast.h"


int main() {
    Lexer intr = {"(2+2 - (21 * 21 + (3+4) + (5+4 + (54 + 1)))) * 2 ", 0};

    int v = expr(&intr);

    AST ast = createAST();
    printf(ast.toString(&ast));

    printf("%d", v);
    return 0;
}
