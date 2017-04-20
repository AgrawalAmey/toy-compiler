#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./utils.h"

// Create ht
hashTable *
createHashtable()
{
    int size = 50;
    int i;
    hashTable * ht = NULL;

    ht = (hashTable *) malloc(sizeof(hashTable));

    ht->table = malloc(sizeof(hashTableEntry *) * size);

    for (i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }

    ht->size = size;

    return ht;
}

// Hash string
int
getHash(hashTable * ht, char * key)
{
    unsigned long hash = 5381;
    int c;

    while (c = *key++) {
        //  hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }

    return hash % ht->size;
}

// Create key-data pair.
hashTableEntry *
createHashtablePair(char * key, tableEntry data)
{
    hashTableEntry * newpair;

    newpair = malloc(sizeof(hashTableEntry));

    newpair->key = strdup(key);

    newpair->data = data;

    newpair->next = NULL;

    return newpair;
}

// Insert into hashTable.
int
insertInHashtable(hashTable * ht, char * key, tableEntry data, int mode)
{
    int bin = 0;
    hashTableEntry * newpair = NULL;
    hashTableEntry * next    = NULL;
    hashTableEntry * last    = NULL;

    bin = getHash(ht, key);

    next = ht->table[bin];

    while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
        last = next;
        next = next->next;
    }

    if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
        // If the it was undeclared statement chill
        if (next->data.isDefined == 0 && mode == 1) {
            free(&(next->data));
            next->data = data;
            return 1;
        }
        // Clashing defs of module or var
        return -1;
    } else {
        newpair = createHashtablePair(key, data);

        if (next == ht->table[bin]) {
            newpair->next  = next;
            ht->table[bin] = newpair;
        } else if (next == NULL) {
            last->next = newpair;
        } else {
            newpair->next = next;
            last->next    = newpair;
        }

        return 1;
    }
} /* insertInHashtable */

// Find a pair
int
findInHashtable(hashTable * ht, char * key, tableEntry * data)
{
    int bin = 0;
    hashTableEntry * pair;

    bin = getHash(ht, key);

    pair = ht->table[bin];
    while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0) {
        pair = pair->next;
    }

    if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0) {
        return -1;
    } else {
        data = &(pair->data);
        return 1;
    }
}

// Print hash table
char *
printHashtable(hashTable * ht)
{
    int i = 0;
    hashTableEntry * next;

    // Itrate over bins
    for (i = 0; i < 50; i++) {
        next = ht->table[i];
        while (next != NULL) {
            printf("%s\n", next->key);
            next = next->next;
        }
    }
    hashTableEntry * pair;
}
