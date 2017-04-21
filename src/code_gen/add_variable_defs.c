#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./code_gen.h"
#include "../utils/utils.h"

void
addVaribleDefs(STTNode ** root, char * buffer)
{
    int i;

    if (*root == NULL) {
        return;
    }

    printVaribleDefs((**root).table, (**root).scopeId, buffer);

    for (i = 0; i < 20; i++) {
        addVaribleDefs(&((**root).children[i]), buffer);
    }
}

char *
printVaribleDefs(hashTable * ht, int scopeId, char * buffer)
{
    int i = 0;
    hashTableEntry * next;
    char temp[20];

    // Itrate over bins
    for (i = 0; i < 50; i++) {
        next = ht->table[i];
        while (next != NULL) {
            if (next->data.type == ARRAY) {
                sprintf(temp, "\t%s_%d times %d db 0\n", next->key, scopeId,
                  next->data.endRange - next->data.startRange + 1);
            } else {
                sprintf(temp, "\t%s_%d db 0\n", next->key, scopeId);
            }
            strcat(buffer, temp);
            next = next->next;
        }
    }
    hashTableEntry * pair;
}
