#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./code_gen.h"
#include "../utils/utils.h"
#include "../symbol_table/symbol_table.h"

// Called when an ioStmt is encountered
void
addAssignStmt(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count)
{
    int i, scopeId;
    tableEntry * data;
    char temp[50];


    if (*t == NULL) {
        return;
    }

    // assignmentStmt ID (lvalueIDStmt | lvalueARRStmt)
    // lvalueIDStmt
    if ((**t).children[1]->data.name == lvalueIDStmt) {
        // lvalueIDStmt expression
        // Evaluate expression (evalued expression is stored at __result__)
        addExpression(&((**t).children[1]->children[0]), sT, buffer, lable_count);

        scopeId = getEntryFromSTT((**t).children[0]->data.string, data, (**t).scopeId, sT);
        strcat(buffer, "\tmov eax, [__result__]\n");
        sprintf(temp, "\tmov [%s_%d], eax\n", (**t).children[0]->data.string, scopeId);
        strcat(buffer, temp);
        // lvalueARRStmt (NUM | ID) expression
    } else {
        // Evaluate expression (evalued expression is stored at __result__)
        addExpression(&((**t).children[1]->children[1]), sT, buffer, lable_count);

        // NUM
        if ((**t).children[1]->children[0]->data.name == NUM) {
            sprintf(temp, "\tmov eax, %s\n", (**t).children[0]->data.string);
            strcat(buffer, temp);
            // ID
        } else {
            scopeId = getEntryFromSTT((**t).children[1]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[1]->children[0]->data.string, scopeId);
            strcat(buffer, temp);
        }
        strcat(buffer, "\tmov ebx, [__result__]\n");
        scopeId = getEntryFromSTT((**t).children[0]->data.string, data, (**t).scopeId, sT);
        sprintf(temp, "\tmov [%s_%d + 4 * ebx], eax\n", (**t).children[0]->data.string, scopeId);
        strcat(buffer, temp);
    }
} /* addAssignStmt */
