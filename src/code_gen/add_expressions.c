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
        addExpression(t, sT, buffer, lable_count);
    }

    if ((**t).data.name == expression) {
        strcat(buffer, "pop [__result__]");
        if ((**t).children[0]->data.name == MINUS) {
            strcat(buffer, "mov eax, [__result__]");
            strcat(buffer, "neg eax");
            strcat(buffer, "mov [__result__], eax");
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
            if ((**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "mov eax, 0");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov eax, [%s_%d + 4 * eax]\n", (**t).children[0]->children[0]->data.string, scopeId);
            strcat(buffer, temp);
        }


        // NUM
        if ((**t).children[0]->children[1]->data.name == NUM) {
            if ((**t).data.name == PLUS) {
                sprintf(temp, "\tadd eax, %s\n", (**t).children[0]->children[1]->data.string);
            } else if ((**t).data.name == MINUS) {
                sprintf(temp, "\tsub eax, %s\n", (**t).children[0]->children[1]->data.string);
            } else if ((**t).data.name == AND) {
                sprintf(temp, "\tand eax, %s\n", (**t).children[0]->children[1]->data.string);
            } else {
                sprintf(temp, "\tor eax, %s\n", (**t).children[0]->children[1]->data.string);
            }
            strcat(buffer, temp);
            // ID
        } else {
            if ((**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov ebx, [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "mov ebx, 0");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
            if ((**t).data.name == PLUS) {
                sprintf(temp, "\tadd eax, [%s_%d + 4 * ebx]\n", (**t).children[0]->children[1]->data.string, scopeId);
            } else if ((**t).data.name == MINUS) {
                sprintf(temp, "\tsub eax, [%s_%d + 4 * ebx]\n", (**t).children[0]->children[1]->data.string, scopeId);
            } else if ((**t).data.name == AND) {
                sprintf(temp, "\tand eax, [%s_%d + 4 * ebx]\n", (**t).children[0]->children[1]->data.string, scopeId);
            } else {
                sprintf(temp, "\tor eax, [%s_%d + 4 * ebx]\n", (**t).children[0]->children[1]->data.string, scopeId);
            }
            strcat(buffer, temp);
        }

        strcat(buffer, "push eax");
    }

    if ((**t).data.name == MUL || (**t).data.name == DIV) {
        // NUM
        if ((**t).children[0]->children[0]->data.name == NUM) {
            sprintf(temp, "\tmov eax, %s\n", (**t).children[0]->children[0]->data.string);
            strcat(buffer, temp);
            // ID
        } else {
            if ((**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "mov eax, 0");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov eax, [%s_%d + 4 * eax]\n", (**t).children[0]->children[0]->data.string, scopeId);
            strcat(buffer, temp);
        }

        if ((**t).data.name == DIV) {
            strcat(buffer, "mov	edx, 0");
        }

        // NUM
        if ((**t).children[0]->children[1]->data.name == NUM) {
            if ((**t).data.name == MUL) {
                sprintf(temp, "\timul dword %s\n", (**t).children[0]->children[1]->data.string);
            } else {
                sprintf(temp, "\tidiv dword %s\n", (**t).children[0]->children[1]->data.string);
            }
            strcat(buffer, temp);
            // ID
        } else {
            if ((**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov ebx [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "mov ebx, 0");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
            if ((**t).data.name == MUL) {
                sprintf(temp, "\timul dword [%s_%d + 4 * ebx]\n", (**t).children[0]->children[1]->data.string, scopeId);
            } else {
                sprintf(temp, "\tidiv dword [%s_%d + 4 * ebx]\n", (**t).children[0]->children[1]->data.string, scopeId);
            }
            strcat(buffer, temp);
        }

        strcat(buffer, "push eax");
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
            if ((**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "mov eax, 0");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov eax, [%s_%d + 4 * eax]\n", (**t).children[0]->children[0]->data.string, scopeId);
            strcat(buffer, temp);
        }

        // NUM
        if ((**t).children[0]->children[1]->data.name == NUM) {
            sprintf(temp, "\tmov ebx, %s\n", (**t).children[0]->children[1]->data.string);
            strcat(buffer, temp);
            // ID
        } else {
            if ((**t).children[0]->children[1]->data.name == ID) {
                scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov ebx [%s_%d]\n", (**t).children[0]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "mov ebx, 0");
            }
            scopeId = getEntryFromSTT((**t).children[0]->children[1]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tmov ebx [%s_%d + 4 * ebx]\n", (**t).children[0]->children[1]->data.string, scopeId);
            strcat(buffer, temp);
        }

        if ((**t).data.name == EQ) {
            sprintf(buffer, "je .true_%d", *lable_count);
        } else if ((**t).data.name == NE) {
            sprintf(buffer, "jne .true_%d", *lable_count);
        } else if ((**t).data.name == GE) {
            sprintf(buffer, "jge .true_%d", *lable_count);
        } else if ((**t).data.name == GT) {
            sprintf(buffer, "jg .true_%d", *lable_count);
        }  else if ((**t).data.name == LE) {
            sprintf(buffer, "jle .true_%d", *lable_count);
        } else {
            sprintf(buffer, "jl .true_%d", *lable_count);
        }
        strcat(buffer, temp);
        sprintf(buffer, "jmp .end_%d", *lable_count);
        strcat(buffer, temp);
        strcat(buffer, "push 0");
        sprintf(buffer, ".true_%d:", *lable_count);
        strcat(buffer, temp);
        strcat(buffer, "push 1");
        sprintf(buffer, ".end_%d:", *lable_count);
        strcat(buffer, temp);
        (*lable_count)++;
    }
} /* addAssignStmt */
