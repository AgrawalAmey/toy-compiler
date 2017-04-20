#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "../utils/utils.h"
#include "./symbol_table.h"

STTNode **
createSTT()
{
    STTNode ** root;

    root  = (STTNode **) malloc(sizeof(STTNode *));
    *root = NULL;
    return root;
}

// Inserts node as children to given node
int
insertInSTT(char * name, int parentScopeId, STTNode ** root)
{
    int static nodeCount = 0;
    int result, i;

    // First node of tree or scopeIds matches
    if (parentScopeId == -1 || (*root != NULL && (**root).scopeId == parentScopeId)) {
        // Add the node
        insertSTTNode(name, nodeCount, root);
        nodeCount++;
        return nodeCount - 1;
    } else if (*root != NULL) {
        // Recurse
        for (i = 0; i < 20; i++) {
            result = insertInSTT(name, parentScopeId, &((**root).children[i]));
            if (result >= 0) {
                return result;
            }
        }
    } else {
        // Empty pointer and is not root
        return -1;
    }
}

// Add a node to given parent
void
insertSTTNode(char * name, int scopeId, STTNode ** parent)
{
    int i;
    STTNode * temp;

    temp = (STTNode *) malloc(sizeof(STTNode));
    // We have set maximum number of children at 20
    for (i = 0; i < 20; i++) {
        temp->children[i] = NULL;
    }

    strcpy(temp->name, name);
    temp->table   = createHashtable();
    temp->scopeId = scopeId;
    temp->parent  = *parent;

    // If tree is empty make it the root
    if (*parent == NULL) {
        *parent = temp;
    } else {
        // Find the first free pointer of
        i = 0;
        while ((**parent).children[i] != NULL) {
            i++;
        }
        (**parent).children[i] = temp;
    }
}

void
printSTTInOrder(STTNode ** root)
{
    int i;

    if (*root == NULL) {
        return;
    }
    printf("Name:%s Id:%d\n", (**root).name, (**root).scopeId);
    printHashtable((**root).table);
    for (i = 0; i < 20; i++) {
        printSTTInOrder(&((**root).children[i]));
    }
    printf("-----------------------------------------\n");
}
