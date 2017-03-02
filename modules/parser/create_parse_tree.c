#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/parser.h"
#include "../../headers/utils.h"

void creatParseTree(parse_table pt, tree t, Token *input){
    // Initialize stack
    stack s;
    s = createStack();
    push(eof, s);
    push(program, s);

    // Initialize tree
    token __program[] = { program };
    insertInTree(__program, t);

    int readHead = 0;
    token tok;
    int i = 0;
    int j;

    while(isStackEmpty(s) != 1){
        tok = pop(s);

        // Index of terminals start from 1000
        if (tok >= 1000){
            if(tok == input[readHead].name){
                insertLeafData(input[readHead], t);
                readHead++;
            } else {
                printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is %s",
                token_to_string(input[readHead].name), input[readHead].string, input[readHead].line_number, token_to_string(tok));
            }
        } else {
            if(pt[tok-500][input[readHead].name-1000][0] != 0){
                // Find the end of rule
                while(pt[tok-500][input[readHead].name-1000][i] != 0){
                    i++;
                }
                i--;
                // Insert the rule to stack in reverse order
                while(i >= 0){
                    if(pt[tok-500][input[readHead].name-1000][i] != EPSILON){
                        push(pt[tok-500][input[readHead].name-1000][i], s);
                    }
                    i--;
                }

                // Insert into tree
                insertInTree(pt[tok-500][input[readHead].name-1000], t);

            } else {
                printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is ",
                token_to_string(input[readHead].name), input[readHead].string, input[readHead].line_number);
                for (j = 0; j < 100; j++) {
                    if (pt[tok-500][j][0] != 0) {
                        printf("%s ", token_to_string(j+1000));
                    }
                }
                printf("\n");
            }
        }
    }
}
