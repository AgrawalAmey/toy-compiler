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
addExpression(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count)
{
    int i, scopeId;
    tableEntry * data;
    char temp[50];

    if (*t == NULL) {
        return;
    }

    for (i = 0; i < 20; i++) {
        addExpression(&((**t).children[i]), sT, buffer, lable_count);
    }

    if ((**t).data.name == expression) {
        strcat(buffer, "\tpop [__result__]\n");
        if ((**t).children[0]->data.name == MINUS) {
            strcat(buffer, "\tmov eax, [__result__]\n");
            strcat(buffer, "\tneg eax\n");
            strcat(buffer, "\tmov [__result__], eax\n");
        }
    }

    if ((**t).data.name == PLUS || (**t).data.name == MINUS ||
      (**t).data.name == AND || (**t).data.name == OR)
    {
        // NUM

        if ((**t).children[0]->children[0]->data.name == NUM) {
            sprintf(temp, "\tmov eax, %s\n", (**t).children[0]->children[0]->data.string);
            strcat(buffer, temp);
            // ID
        } else {
            if ((**t).children[0]->children[1] != NULL && (**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "\tmov eax, 0\n");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov eax, [%s_%d + 4 * eax]\n", (**t).children[0]->children[0]->data.string, scopeId);
            strcat(buffer, temp);
        }


        // NUM
        if ((**t).children[1]->children[0]->data.name == NUM) {
            if ((**t).data.name == PLUS) {
                sprintf(temp, "\tadd eax, %s\n", (**t).children[1]->children[0]->data.string);
            } else if ((**t).data.name == MINUS) {
                sprintf(temp, "\tsub eax, %s\n", (**t).children[1]->children[0]->data.string);
            } else if ((**t).data.name == AND) {
                sprintf(temp, "\tand eax, %s\n", (**t).children[1]->children[0]->data.string);
            } else {
                sprintf(temp, "\tor eax, %s\n", (**t).children[1]->children[0]->data.string);
            }
            strcat(buffer, temp);
            // ID
        } else {
            if ( (**t).children[1]->children[0] != NULL && (**t).children[1]->children[0]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[1]->children[0]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov ebx, [%s_%d]\n", (**t).children[1]->children[0]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "\tmov ebx, 0\n");
            }
            scopeId = getEntryFromSTT((**t).children[1]->children[0]->data.string, data, (**t).scopeId, sT);
            if ((**t).data.name == PLUS) {
                sprintf(temp, "\tadd eax, [%s_%d + 4 * ebx]\n", (**t).children[1]->children[0]->data.string, scopeId);
            } else if ((**t).data.name == MINUS) {
                sprintf(temp, "\tsub eax, [%s_%d + 4 * ebx]\n", (**t).children[1]->children[0]->data.string, scopeId);
            } else if ((**t).data.name == AND) {
                sprintf(temp, "\tand eax, [%s_%d + 4 * ebx]\n", (**t).children[1]->children[0]->data.string, scopeId);
            } else {
                sprintf(temp, "\tor eax, [%s_%d + 4 * ebx]\n", (**t).children[1]->children[0]->data.string, scopeId);
            }
            strcat(buffer, temp);
        }

        strcat(buffer, "\tpush eax\n");
    }

    if ((**t).data.name == MUL || (**t).data.name == DIV) {
        // NUM
        if ((**t).children[0]->children[0]->data.name == NUM) {
            sprintf(temp, "\tmov eax, %s\n", (**t).children[0]->children[0]->data.string);
            strcat(buffer, temp);
            // ID
        } else {
            if ( (**t).children[0]->children[1] != NULL && (**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "\tmov eax, 0\n");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov eax, [%s_%d + 4 * eax]\n", (**t).children[0]->children[0]->data.string, scopeId);
            strcat(buffer, temp);
        }

        if ((**t).data.name == DIV) {
            strcat(buffer, "\tmov	edx, 0\n");
        }

        // NUM
        if ((**t).children[1]->children[0]->data.name == NUM) {
            if ((**t).data.name == MUL) {
                sprintf(temp, "\timul dword %s\n", (**t).children[1]->children[0]->data.string);
            } else {
                sprintf(temp, "\tidiv dword %s\n", (**t).children[1]->children[0]->data.string);
            }
            strcat(buffer, temp);
            // ID
        } else {
            if ((**t).children[1]->children[0] != NULL && (**t).children[1]->children[0]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[1]->children[0]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov ebx [%s_%d]\n", (**t).children[1]->children[0]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "\tmov ebx, 0\n");
            }
            scopeId = getEntryFromSTT((**t).children[1]->children[0]->data.string, data, (**t).scopeId, sT);
            if ((**t).data.name == MUL) {
                sprintf(temp, "\timul dword [%s_%d + 4 * ebx]\n", (**t).children[1]->children[0]->data.string, scopeId);
            } else {
                sprintf(temp, "\tidiv dword [%s_%d + 4 * ebx]\n", (**t).children[1]->children[0]->data.string, scopeId);
            }
            strcat(buffer, temp);
        }

        strcat(buffer, "\tpush eax\n");
    }

    if ((**t).data.name == GE || (**t).data.name == GT ||
      (**t).data.name == LT || (**t).data.name == GE ||
      (**t).data.name == EQ || (**t).data.name == NE)
    {
        // NUM
        if ((**t).children[0]->children[0]->data.name == NUM) {
            sprintf(temp, "\tmov eax, %s\n", (**t).children[0]->children[0]->data.string);
            strcat(buffer, temp);
            // ID
        } else {
            if ((**t).children[0]->children[1] != NULL && (**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "\tmov eax, 0\n");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov eax, [%s_%d + 4 * eax]\n", (**t).children[0]->children[0]->data.string, scopeId);
            strcat(buffer, temp);
        }

        // NUM
        if ((**t).children[1]->children[0]->data.name == NUM) {
            sprintf(temp, "\tmov ebx, %s\n", (**t).children[1]->children[0]->data.string);
            strcat(buffer, temp);
            // ID
        } else {
            if ((**t).children[1]->children[0] != NULL && (**t).children[1]->children[0]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[1]->children[0]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov ebx [%s_%d]\n", (**t).children[1]->children[0]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "\tmov ebx, 0\n");
            }
            scopeId = getEntryFromSTT((**t).children[1]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov ebx [%s_%d + 4 * ebx]\n", (**t).children[1]->children[0]->data.string, scopeId);
            strcat(buffer, temp);
        }

        if ((**t).data.name == EQ) {
            sprintf(buffer, "\tje .true_%d\n", *lable_count);
        } else if ((**t).data.name == NE) {
            sprintf(buffer, "\tjne .true_%d\n", *lable_count);
        } else if ((**t).data.name == GE) {
            sprintf(buffer, "\tjge .true_%d\n", *lable_count);
        } else if ((**t).data.name == GT) {
            sprintf(buffer, "\tjg .true_%d\n", *lable_count);
        }  else if ((**t).data.name == LE) {
            sprintf(buffer, "\tjle .true_%d\n", *lable_count);
        } else {
            sprintf(buffer, "\tjl .true_%d\n", *lable_count);
        }
        strcat(buffer, temp);
        sprintf(buffer, "\tjmp .end_%d\n", *lable_count);
        strcat(buffer, temp);
        strcat(buffer, "\tpush 0\n");
        sprintf(buffer, "\t.true_%d:\n", *lable_count);
        strcat(buffer, temp);
        strcat(buffer, "\tpush 1\n");
        sprintf(buffer, "\t.end_%d:\n", *lable_count);
        strcat(buffer, temp);
        (*lable_count)++;
    }
} /* addAssignStmt */
