// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./types/token.h"
#include "./types/structs.h"
#include "./utils/utils.h"
#include "./lexer/lexer.h"
#include "./parser/parser.h"
#include "./ast/ast.h"
#include "./symbol_table/symbol_table.h"

void
main(int argc, char * argv[])
{
    int userChoice = 0;
    int i = 0;
    int lexerSuccess  = 0;
    int parserSuccess = 0;

    // File open
    char dirtyBuffer[4000] = { '\0' };
    char cleanBuffer[4000] = { '\0' };

    parse_table pt;
    parseTree t;
    hashTable * fT;
    symbolTableTree sT;

    t = createEmptyParseTree();

    sT = createSTT();

    fT = createHashtable();

    Token input[1000];

    int fileLen = 0;

    createParseTable("../lang/grammer.txt", pt);

    lexerSuccess = getTokens(argv[1], input);

    parserSuccess = createParseTree(pt, t, input);

    createAST(t);

    FILE * fp_in;
    FILE * fp_out;
    fp_in = fopen(argv[1], "r");
    if (fp_in == NULL) {
        printf("Input file does not exist.\n");
        return;
    }

    fread(dirtyBuffer, 1, 4000, fp_in);

    removeComments(dirtyBuffer, cleanBuffer);

    do {
        printf("---------------------------------------------------\n");
        printf("First and follow set automated\n");
        printf("Both lexical and syntax analysis modules implemented\n");
        printf("Please select one the option:\n");
        printf("---------------------------------------------------\n");
        printf("1. Print the comment free code on the console.\n");
        printf("2. Print the tokens list.\n");
        printf("3. Check the symantic correctness of code.\n");
        printf("4. Print the parse tree.\n");
        printf("5. Print the AST.\n");
        printf("6. Print the symbol table tree.\n");
        printf("7. Exit.\n");
        printf("---------------------------------------------------\n");
        scanf("%d", &userChoice);
        printf("---------------------------------------------------\n");
        switch (userChoice) {
            case 1:
                printf("Comment free code:\n");
                printf("%s\n", cleanBuffer);
                break;
            case 2:
                if (lexerSuccess == -1) {
                    printf("The code is syntactically incorrect.\n");
                }
                i = 0;
                printf("Input tokens:\n");
                while (input[i].name != eof) {
                    printf("%s %s %d\n", input[i].string, token_to_string(input[i].name), input[i].line_number);
                    i++;
                }
                break;
            case 3:
                if (lexerSuccess == -1 || parserSuccess == -1) {
                    printf("The code is syntactically incorrect.\n");
                } else {
                    printf("The code is syntactically correct.\n");
                }
                break;
            case 4:
                printASTPostOrder(t);
                // fp_out = fopen(argv[2], "w+");
                // if (fp_out == NULL) {
                //     printf("Output file does not exist.\n");
                //     return;
                // }
                // printTreeToFile(fp_out, t);
                // fclose(fp_out);
                // printf("Tree written to file\n");
                break;
            case 5:
                printASTPostOrder(t);
                break;
            case 6:
                populateSymbolTable(t, sT, fT);
                printSTTInOrder(sT);
                printf("Function Table:\n");
                printHashtable(fT);
                break;
            case 7:
                break;
            default:
                printf("Invalid option. Please select again.\n");
                break;
        }
    } while (userChoice != 7);
} /* main */
