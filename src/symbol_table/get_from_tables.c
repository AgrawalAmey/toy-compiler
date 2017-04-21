#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "../utils/utils.h"
#include "./symbol_table.h"

// Get an entry in symbol table
int
getEntryFromSTT(char * key, tableEntry * data, int scopeId, STTNode ** root)
{
    int result, i;

    if (*root == NULL) {
        return -1;
    }

    if ((**root).scopeId == scopeId) {
        // Get here
        result = findInHashtable((**root).table, key, data);
        // Not found
        if (result == -1) {
            return -2;
        }
        // Found it
        return (**root).scopeId;
    }

    // Recurse
    for (i = 0; i < 20; i++) {
        result = getEntryFromSTT(key, data, scopeId, &((**root).children[i]));
        if (result != -1) {
            return result;
        }
    }
    // If result == -1
    // Try finding in yourself
    result = findInHashtable((**root).table, key, data);
    // Not found
    if (result == -1) {
        return -1;
    } else if (result == -1) {
        printf("Error: %s is undefined.\n", key);
        return -2;
    } else {
        return (**root).scopeId;
    }
} /* getEntryFromSTT */

// Get an entry in symbol table
int
getEntryFromFT(char * key, tableEntry * data, hashTable * fT)
{
    int result;

    result = findInHashtable(fT, key, data);

    if (result == -1) {
        printf("Error: %s is not defined.\n", key);
        return -1;
    }

    return 1;
}
