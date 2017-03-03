#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../custom_types/token.h"
#include "../../../custom_types/structs.h"
#include "../../../headers/utils.h"
#include "../../../headers/lexer.h"


int main(int agrc, char * argv[] )
{
	Token input[1000];
	int i = 0;

	getTokens("../../../test_cases/testcase5.txt", input);

    printf("Tokenization finished.\n");

    while (input[i].name != eof) {
        printf("%s %s %d\n", input[i].string, token_to_string(input[i].name), input[i].line_number);
        i++;
    }
	return 0;
}
