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
    } else if ((**root).scopeId == scopeId) {
        // Get here
        result = findInHashtable((**root).table, key, data);
        // Clash occured while inserting
        if (result == -1) {
            printf("Error: %s is not defined.\n", key);
            return -1;
        }
        return 1;
    } else {
        // Recurse
        for (i = 0; i < 20; i++) {
            result = getEntryFromSTT(key, data, scopeId, &((**root).children[i]));
            if (result >= 0) {
                return result;
            }
        }
    }
}

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
