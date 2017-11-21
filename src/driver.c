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
#include "./code_gen/code_gen.h"

void
main(int argc, char * argv[])
{
    int userChoice = 0;
    int i   = 0;
    int num = 0;

    // File open
    char dirtyBuffer[4000] = { '\0' };
    char cleanBuffer[4000] = { '\0' };

    parse_table pt;
    parseTree t;
    hashTable * fT;
    symbolTableTree sT;


    Token input[1000];

    int fileLen = 0;


    FILE * fp_in;
    FILE * fp_out;

    fp_in = fopen(argv[1], "r");
    if (fp_in == NULL) {
        printf("Input file does not exist.\n");
        return;
    }

    fread(dirtyBuffer, 1, 4000, fp_in);

    removeComments(dirtyBuffer, cleanBuffer);

    int lexerSuccess  = 0;
    int parserSuccess = 0;

    t = createEmptyParseTree();

    sT = createSTT();

    fT = createHashtable();

    createParseTable("../lang/grammer.txt", pt);
    lexerSuccess = getTokens(argv[1], input);

    parserSuccess = createParseTree(pt, t, input);

    printf("---------------------------------------------------\n");
    printf("First and follow set automated\n");
    printf("Both lexical and syntax analysis modules implemented\n");
    printf("Please select one the option:\n");
    printf("---------------------------------------------------\n");
    // printf("1. Print the comment free code on the console.\n");
    printf("1. Print the tokens list on console.\n");
    printf("2. Check the syntactic correctness of code and generate parse tree.\n");
    //       printf("4. Print the parse tree.\n");
    printf("3. Print the AST.\n");
    printf("4. Display amount of memory and nodes for PT and AST and percentage of memory freed.\n");
    printf("5. Print Symbol Tree.\n");
    printf("6. Print Aseembley code.\n");
    printf("7. Exit.\n");
    printf("---------------------------------------------------\n");
    scanf("%d", &userChoice);
    printf("---------------------------------------------------\n");
    switch (userChoice) {
        case 1:
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
        case 2:
            if (lexerSuccess == -1 || parserSuccess == -1) {
                printf("The code is syntactically incorrect.\n");
            } else {
                printf("The code is syntactically correct.\n");
            }
            break;
        case 4:
            countNodes(t, &num);
            printf("Parse tree: %d %ld\n", num, num * sizeof(parseTreeNode));
            num = 0;
            createAST(t);
            countNodes(t, &num);
            printf("ASt: %d %ld\n", num, num * sizeof(parseTreeNode));
            break;
        case 3:
            createAST(t);
            printf("AST will be printed in post-order\n");
            printASTPostOrder(t);
            break;
        case 5:
            createAST(t);
            populateSymbolTable(t, sT, fT);
            printSTTInOrder(sT);
            printf("Function Table:\n");
            printHashtable(fT);
            break;
        case 6:
            createAST(t);
            populateSymbolTable(t, sT, fT);
            genarateCode(t, sT);
            break;
        case 7:
            break;
        default:
            printf("Invalid option. Please select again.\n");
            break;
    }
} /* main */
