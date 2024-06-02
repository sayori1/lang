#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "str_utils.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include "interpreter.h"


int main() {
    Lexer lexer = createLexer("(2+43 + (3+4 * (454+334+ 12))");

    Parser parser = {&lexer};

    Interpeter intr = {&parser};

    printf("%d", run(&intr));


    return 0;
}
