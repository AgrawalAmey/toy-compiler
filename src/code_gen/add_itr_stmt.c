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
addItrStmt(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count)
{
    int i, scopeId;
    tableEntry * data;
    char temp[50];
    int lable;

    if (*t == NULL) {
        return;
    }

    // increment the lable count by 1
    lable = *lable_count;
    (*lable_count)++;

    // iterativeStmt FOR ID range statements
    if ((**t).children[0]->data.name == FOR) {
        scopeId = getEntryFromSTT((**t).children[1]->data.string, data, (**t).scopeId, sT);
        sprintf(temp, "\tmov [%s_%d], %s\n", (**t).children[1]->data.string, scopeId,
          (**t).children[2]->children[0]->data.string);
        strcat(buffer, temp);
        sprintf(temp, "\tmov [__temp__], %s\n", (**t).children[2]->children[0]->data.string);
        strcat(buffer, temp);
        sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[1]->data.string, scopeId);
        strcat(buffer, temp);
        strcat(buffer, "\tcmp eax, [__temp__]\n");
        sprintf(temp, "\tjge .end_%d\n", lable);
        strcat(buffer, temp);
        sprintf(temp, "\t.for_%d:\n", lable);
        strcat(buffer, temp);
        // Genarate Code for inner statements
        genarateCodeRecurssively(&((**t).children[3]), sT, buffer, lable_count);
        sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[1]->data.string, scopeId);
        strcat(buffer, temp);
        strcat(buffer, "\tadd eax, 1\n");
        sprintf(temp, "\tmov [%s_%d], eax\n", (**t).children[1]->data.string, scopeId);
        strcat(buffer, temp);
        strcat(buffer, "\tcmp	eax, [__temp__]\n");
        sprintf(temp, "\tjl .for_%d\n", lable);
        strcat(buffer, temp);
        sprintf(temp, "\t.end_%d:\n", lable);
        strcat(buffer, temp);
        // iterativeStmt WHILE arithmeticOrBooleanExpr statements
    } else {
        // Evaluate the condition
        addExpression(&((**t).children[1]), sT, buffer, lable_count);
        strcat(buffer, "\tmov eax, [__result__]\n");
        strcat(buffer, "\tmov [__temp__], eax\n");
        strcat(buffer, "\tcmp eax, 0\n");
        sprintf(temp, "\tjle .end_%d\n", lable);
        strcat(buffer, temp);
        sprintf(temp, "\t.while_%d:\n", lable);
        strcat(buffer, temp);
        // Genarate Code for inner statements
        genarateCodeRecurssively(&((**t).children[2]), sT, buffer, lable_count);
        strcat(buffer, temp);
        strcat(buffer, "\tmov eax, [__temp__]\n");
        strcat(buffer, "\tcmp eax, 0\n");
        sprintf(temp, "\tjg .while_%d\n", lable);
        strcat(buffer, temp);
        sprintf(temp, "\t.end_%d:\n", lable);
        strcat(buffer, temp);
    }
} /* addItrStmt */
