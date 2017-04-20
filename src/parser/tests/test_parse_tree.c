#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./parser.h"
#include "../utils/utils.h"
#include "../lexer/lexer.h"

void
main(int argc, char * argv[])
{
    parse_table pt;
    parseTree t;

    t = createEmptyParseTree();

    Token input[1000];

    creatParseTable("../../../lang/grammer.txt", pt);

    printf("Parse table genration finished.\n");

    getTokens("../../../test_cases/testcase2.txt", input);

    printf("Tokenization finished.\n");

    createParseTree(pt, t, input);

    printf("Parse tree genration finished.\n");

    printInorder(t);
}
