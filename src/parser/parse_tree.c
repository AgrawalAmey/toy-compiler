#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./parser.h"
#include "../utils/utils.h"

parseTreeNode **
createEmptyParseTree()
{
    parseTreeNode ** root;

    root  = (parseTreeNode **) malloc(sizeof(parseTreeNode *));
    *root = NULL;
    return root;
}

// Inserts nodes as children to given node
void
insertParseTreeNodes(token * vals, parseTreeNode ** root)
{
    int i = 0;
    int j = 0;

    // Assumes that the node has no children initially
    while (vals[i] != 0) {
        parseTreeNode * temp;
        temp = (parseTreeNode *) malloc(sizeof(parseTreeNode));
        // We have set maximum number of children at 10
        for (j = 0; j < 20; j++) {
            temp->children[j] = NULL;
        }

        temp->associated = 0;
        temp->scopeId    = -1;
        temp->data.name  = vals[i];
        temp->parent     = *root;

        // For root node insertion
        if (*root == NULL) {
            *root = temp;
            return;
        } else {
            // Update child pointer of parent
            (**root).children[i] = temp;
        }

        i++;
    }
}

// Insert nodes into tree
int
insertInParseTree(token * vals, parseTreeNode ** tree)
{
    int i = 0;

    // If empty node
    if ((*tree) == NULL) {
        insertParseTreeNodes(vals, tree);
        return 1;
        // For non-terminal nodes
    } else if ((**tree).data.name < 1000) {
        if ((**tree).children[0] == NULL) {
            // Child does not exist so insert here
            insertParseTreeNodes(vals, tree);
            return 1;
        }
        // Try to insert at the left-most children
        for (i = 0; i < 20; i++) {
            if ((**tree).children[i] != NULL) {
                if (insertInParseTree(vals, &((**tree).children[i]))) {
                    return 1;
                }
            }
        }

        return 0;
        // The node is a terminal
    } else {
        return 0;
    }
}

int
insertLeafDataInParseTree(Token t, parseTreeNode ** tree)
{
    int i;

    // Should never be called before tree is made
    if (*tree != NULL) {
        // Base case: if node is a terminal and unassigned
        if ((**tree).data.name >= 1000 && (**tree).data.name != EPSILON && !(**tree).associated) {
            (**tree).data       = t;
            (**tree).associated = 1;
            return 1;
        } else {
            // Try to insert into children
            for (i = 0; i < 20; i++) {
                if ((**tree).children[i] != NULL) {
                    if (insertLeafDataInParseTree(t, &((**tree).children[i]))) {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
}

void
printParseTreeInorder(parseTreeNode ** tree)
{
    int i;

    if (*tree != NULL) {
        printParseTreeInorder(&((**tree).children[0]));
        // If is a terminal or leaf in other words
        if ((**tree).data.name >= 1000 && (**tree).data.name != EPSILON) {
            printf("| %25s | %25d | %25s | %25s | %25s | %25s | %25s |\n\n", (**tree).data.string,
              (**tree).data.line_number,
              token_to_string(
                  (**tree).data.name), (**tree).data.string, "yes",
              token_to_string((*(**tree).parent).data.name), token_to_symbol((**tree).data.name));
        } else {
            // If parent is null (Only possible with with non-terminal root)
            if ((**tree).parent == NULL) {
                printf("| %25s | %25s | %25s | %25s | %25s | %25s | %25s |\n\n", "---", "---",
                  token_to_string((**tree).data.name), "---", "no", "ROOT", token_to_string((**tree).data.name));
            } else {
                printf("| %25s | %25s | %25s | %25s | %25s | %25s | %25s |\n\n",
                  "---", "---", token_to_string((**tree).data.name), "---", "no",
                  token_to_string((*(**tree).parent).data.name), token_to_string((**tree).data.name));
            }
        }

        for (i = 1; i < 20; i++) {
            printParseTreeInorder(&((**tree).children[i]));
        }
    }
}
