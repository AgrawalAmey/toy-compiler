#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./code_gen.h"
#include "../utils/utils.h"

void
genarateCode(parseTreeNode ** t, STTNode ** sT)
{
    if (*t == NULL) {
        return;
    }

    char * buffer;

    buffer = (char *) malloc(40000 * sizeof(char));

    int * lable_count;
    lable_count  = (int *) malloc(sizeof(int));
    *lable_count = 0;

    // The setup line
    strcpy(buffer, "extern printf\n");
    strcat(buffer, "extern scanf\n");
    strcat(buffer, "global main\n");

    // Get the data setment printed
    strcat(buffer, "\nSECTION .data\n");
    strcat(buffer, "\tprint_int: db \"%d\", 10, 0\n");
    strcat(buffer, "\tscan_int: db \"%d\", 0\n");
    strcat(buffer, "\t__result__: db 0\n");
    strcat(buffer, "\t__temp__: db 0\n");
    // Add variables
    addVaribleDefs(sT, buffer);

    // Main method begings
    strcat(buffer, "\nSECTION .text\n");
    strcat(buffer, "\tmain:\n");

    // Add statements
    genarateCodeRecurssively(t, sT, buffer, lable_count);

    // Exit lines
    strcat(buffer, "\tmov eax, 0\n");
    strcat(buffer, "\tret\n");

    // Print
    printf("%s\n", buffer);
} /* genarateCode */

void
genarateCodeRecurssively(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count)
{
    int i;

    if (*t == NULL) {
        return;
    }

    switch ((**t).data.name) {
        case ioStmt:
            addIOStmt(t, sT, buffer);
            break;
        case assignmentStmt:
            addAssignStmt(t, sT, buffer, lable_count);
            break;
        case iterativeStmt:
            addItrStmt(t, sT, buffer, lable_count);
            // Go rightwards but not downwards
            genarateCodeRecurssively(&((**t).right), sT, buffer, lable_count);
            return;

        case conditionalStmt:
            addCondStmt(t, sT, buffer, lable_count);
            // Go rightwards but not downwards
            genarateCodeRecurssively(&((**t).right), sT, buffer, lable_count);
            return;
    }

    // Top down
    for (i = 0; i < 20; i++) {
        genarateCodeRecurssively(&((**t).children[i]), sT, buffer, lable_count);
    }

    // left to right
    genarateCodeRecurssively(&((**t).right), sT, buffer, lable_count);
} /* genarateCodeRecurssively */
