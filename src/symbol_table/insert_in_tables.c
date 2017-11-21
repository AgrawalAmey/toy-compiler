#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "../utils/utils.h"
#include "./symbol_table.h"

// Insert an entry in symbol table
int
insertEntryInSTT(char * key, tableEntry data, int scopeId, STTNode ** root)
{
    int result, i;

    if (*root == NULL) {
        return -1;
    } else if ((**root).scopeId == scopeId) {
        // Insert here
        result = insertInHashtable((**root).table, key, data, 0);
        // Clash occured while inserting
        if (result == -1) {
            printf("Error7: %s has clasing declarations.\n", key);
            return -1;
        }
        return 1;
    } else {
        // Recurse
        for (i = 0; i < 20; i++) {
            result = insertEntryInSTT(key, data, scopeId, &((**root).children[i]));
            if (result >= 0) {
                return result;
            }
        }
    }
}

// Insert an entry in symbol table
int
insertEntryInFT(char * key, tableEntry data, hashTable * fT)
{
    int result;

    result = insertInHashtable(fT, key, data, 1);

    if (result == -1) {
        printf("Error7: %s has clasing declarations.\n", key);
        return -1;
    }

    return 1;
}
