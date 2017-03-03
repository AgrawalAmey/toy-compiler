#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../custom_types/token.h"
#include "../../../custom_types/structs.h"
#include "../../../headers/utils.h"
#include "../../../headers/parser.h"
#include "../../../headers/lexer.h"

void main(int argc, char* argv[]){
    int i;

    parse_table pt;
    tree t;
    t = createTree();

    Token input[1000];

    creatParseTable("../../../lang/grammer.txt", pt);

    printf("Parse table is genrated.\n");

    getTokens("../../../test_cases/testcase4.txt", input);

    printf("Tokenization finished.\n");

    while (input[i].name != eof) {
        printf("%s %s %d\n", input[i].string, token_to_string(input[i].name), input[i].line_number);
        i++;
    }

    creatParseTree(pt, t, input);

    printInorder(t);
}
