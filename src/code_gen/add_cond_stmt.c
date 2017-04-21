#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./code_gen.h"
#include "../utils/utils.h"
#include "../symbol_table/symbol_table.h"

void
addCondStmt(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count)
{
    int i, scopeId;
    tableEntry * data;
    char temp[50];
    char idString[20];
    int lable, originalLable;
    parseTreeNode * caseListPointer;

    if (*t == NULL) {
        return;
    }

    originalLable = *lable_count;

    // Load id
    scopeId = getEntryFromSTT((**t).children[0]->data.string, data, (**t).scopeId, sT);
    sprintf(idString, "\tmov eax, [%s_%d]", (**t).children[0]->data.string, scopeId);

    // conditionalStmt ID (list of N9) default
    // N9 value statements
    // Load case list pointer
    caseListPointer = (**t).children[1];
    // Loop
    while (caseListPointer != NULL) {
        // increment the lable count by 1
        lable = *lable_count;
        strcat(buffer, idString);
        if (caseListPointer->children[0]->data.name == TRUE) {
            strcat(buffer, "\tcmp eax, 1\n");
        } else if (caseListPointer->children[0]->data.name == FALSE) {
            strcat(buffer, "\tcmp eax, 0\n");
        } else {
            sprintf(temp, "\tcmp eax, %s\n", caseListPointer->children[0]->data.string);
            strcat(buffer, temp);
        }
        sprintf(temp, "\tje .true_%d\n", lable);
        strcat(buffer, temp);
        sprintf(temp, "\tjmp .end_%d\n", lable);
        strcat(buffer, temp);
        sprintf(temp, "\t.true_%d:\n", lable);
        strcat(buffer, temp);
        // Genarate Code for inner statements
        genarateCodeRecurssively(&(caseListPointer->children[1]), sT, buffer, lable_count);
        sprintf(temp, "\tjmp .end_%d_:\n", originalLable);
        strcat(buffer, temp);
        sprintf(temp, "\t.end_%d:\n", lable);
        strcat(buffer, temp);
        (*lable_count)++;
        caseListPointer = caseListPointer->right;
    }
    // default (list of statements)
    // Genarate Code for inner statements
    genarateCodeRecurssively(&((**t).children[2]), sT, buffer, lable_count);
    sprintf(temp, "\t.end_%d_:\n", originalLable);
    strcat(buffer, temp);
} /* addCondStmt */
