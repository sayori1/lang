#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "str_utils.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"


int main() {
    Lexer lexer = createLexer("2*2+2");

    Parser parser = {&lexer};
    AST* ast = expr(&parser);

    printf(ast->toString(ast));

    return 0;
}
