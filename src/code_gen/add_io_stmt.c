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
addIOStmt(parseTreeNode ** t, STTNode ** sT, char * buffer)
{
    int i, scopeId;
    tableEntry * data;
    char temp[50];


    if (*t == NULL) {
        return;
    }

    // ioStmt GET_VALUE ID
    if ((**t).children[0]->data.name == GET_VALUE) {
        scopeId = getEntryFromSTT((**t).children[1]->data.string, data, (**t).scopeId, sT);
        sprintf(temp, "\tpush dword %s_%d\n", (**t).children[1]->data.string, scopeId);
        strcat(buffer, temp);
        strcat(buffer, "\tpush dword scan_int\n");
        strcat(buffer, "\tcall scanf\n");
        strcat(buffer, "\tadd esp, 8\n");
        // ioStmt PRINT var
    } else {
        // var NUM
        if ((**t).children[1]->children[0]->data.name == NUM) {
            sprintf(temp, "\tpush dword %s\n", (**t).children[1]->children[0]->data.string);
            strcat(buffer, temp);
            // var RNUM
            // var ID whichId
        } else if ((**t).children[1]->children[0]->data.name == ID) {
            // whichId = ID
            if ((**t).children[1]->children[1] != NULL) {
                scopeId = getEntryFromSTT((**t).children[1]->children[1]->data.string, data, (**t).scopeId, sT);
                sprintf(temp, "\tmov eax, [%s_%d]\n", (**t).children[1]->children[1]->data.string, scopeId);
                strcat(buffer, temp);
            } else {
                strcat(buffer, "\tmov eax, 0\n");
            }
            scopeId = getEntryFromSTT((**t).children[1]->children[0]->data.string, data, (**t).scopeId, sT);
            sprintf(temp, "\tpush dword [%s_%d + 4 * eax]\n", (**t).children[1]->children[0]->data.string,
              scopeId);
            strcat(buffer, temp);
        }
        strcat(buffer, "\tpush dword print_int\n");
        strcat(buffer, "\tcall printf\n");
        strcat(buffer, "\tadd esp, 8\n");
    }
} /* addIOStmt */
