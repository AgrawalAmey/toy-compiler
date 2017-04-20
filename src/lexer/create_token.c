#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "../utils/utils.h"
#include "./lexer.h"


Token
createToken(char * lex, int l)
{
    Token tok;

    // we shall use strcmpi for insensitive case string comparison
    tok.line_number = l;
    tok.name        = ID;
    strcpy(tok.string, lex);

    if (string_to_keyword(lex) != 0) {
        tok.name = string_to_keyword(lex);
    }

    return tok;
}
