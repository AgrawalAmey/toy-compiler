#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/parser.h"
#include "../../headers/utils.h"

void creatParseTree(parse_table pt, tree t, Token *input){
    // Initialize stack
    stackNode* s = NULL;
    push(eof, &s);
    push(program, &s);

    // Initialize tree
    token __program[1] = { program };
    insertInTree(__program, t);

    int readHead = 0;
    token tok;
    int i = 0;
    int j;

    while(isStackEmpty(&s) != 1){
        tok = pop(&s);
        // Index of terminals start from 1000
        // Top of stack is terminal
        if (tok >= 1000){
            // Terminals match
            if(tok == input[readHead].name){
                insertLeafData(input[readHead], t);
                readHead++;
            } else {
                // Terminal match failed
                printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is %s.\n",
                token_to_string(input[readHead].name), input[readHead].string, input[readHead].line_number, token_to_symbol(tok));
                return -1;
            }
        } else {
            // Top of stack is non-terminal
            // There exists a table entry for incoming input
            if(pt[tok-500][input[readHead].name-1000][0] != 0){
                i = 0;
                // Find the end of rule
                while(pt[tok-500][input[readHead].name-1000][i] != 0){
                    i++;
                }

                i--;
                // Insert the rule to stack in reverse order
                while(i >= 0){
                    if(pt[tok-500][input[readHead].name-1000][i] != EPSILON){
                        push(pt[tok-500][input[readHead].name-1000][i], &s);
                    }
                    i--;
                }

                // Insert into tree
                insertInTree(pt[tok-500][input[readHead].name-1000], t);

            } else {
                // There is not entry in the table
                // If the rule has an entry for epsilon
                if(pt[tok-500][EPSILON-1000][0] != 0){
                    // pass
                } else {
                    printf("%d\n", pt[tok-500][EPSILON][0]);
                    printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is ",
                    token_to_string(input[readHead].name), input[readHead].string, input[readHead].line_number);
                    for (j = 0; j < 100; j++) {
                        if (pt[tok-500][j][0] != 0 && pt[tok-500][j][0] != EPSILON) {
                            printf("%s ", token_to_symbol(j+1000));
                        }
                    }
                    printf(".\n");
                    return -1;
                }
            }
        }
    }
}
