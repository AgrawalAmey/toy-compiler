// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "../utils/utils.h"
#include "./ast.h"

void
createAST(parseTreeNode ** tree)
{
    int i; // index of child currently visiting

    // If it is a null pointer return
    if (*tree == NULL) {
        return;
    }

    // Try to go right ways
    createAST(&((**tree).right));
    // Reccurse bottom-up
    for (i = 0; i < 20; i++) {
        createAST(&((**tree).children[i]));
    }

    // Remove epsions
    if ((**tree).data.name == EPSILON) {
        free(*tree);
        *tree = NULL;
        return;
    }

    // Remove any child nodes which are useless
    for (i = 0; i < 20; ++i) {
        if ((**tree).children[i] != NULL &&
          isImportantTerminal((**tree).children[i]->data.name) == -1)
        {
            // Free
            // free((**tree).children[i]);
            (**tree).children[i] = NULL;
        }
    }


    // Clean up child pointer array
    removeNullChildren(tree);

    // Remove redundent non-terminals by shifting their child up
    if (isRedundentNonTerminal((**tree).data.name) == 1) {
        parseTreeNode * temp;
        temp = *tree;
        removeNullChildren(tree);
        if ((**tree).children[0] != NULL) {
            (**tree).children[0]->parent = (**tree).parent;
        }
        *tree = (**tree).children[0];
        free(temp);
        return;
    }

    // Remove node with no children which is a non-terminal
    if ((**tree).data.name < 1000) {
        for (i = 0; i < 20; ++i) {
            if ((**tree).children[i] != NULL) {
                break;
            }
        }
        // if all are null remove the node
        if (i == 20) {
            free(*tree);
            *tree = NULL;
            return;
        }
    }

    // Remove the single term recursion cases
    if (isSingleTermRecursionNonTerminal((**tree).data.name) == 1 &&
      (**tree).children[1] == NULL)
    {
        parseTreeNode * listPointer, * temp;
        temp = *tree;
        // Clean up the parent
        // Clean up child pointer array
        removeNullChildren(&(temp->parent));
        // Maybe the parent is not of the same type
        if (temp->parent->data.name != temp->data.name) {
            // Find which one of the parents child is this node
            i = 0;
            while (temp->parent->children[i] != temp) {
                i++;
            }
            // Make the list direct child
            if (temp->children[0] != NULL) {
                temp->children[0]->parent = temp->parent;
            }
            temp->parent->children[i] = temp->children[0];
        } else {
            // Get the first child of parent (which will hold the list)
            if (temp->data.name == N3) {
                listPointer = temp->parent->children[1];
            } else {
                listPointer = temp->parent->children[0];
            }

            // Assign left and right pointers
            listPointer->right      = temp->children[0];
            temp->children[0]->left = listPointer;
            // Nullify the pointer to current node
            if (temp->data.name == N3) {
                temp->parent->children[2] = NULL;
            } else {
                temp->parent->children[1] = NULL;
            }
        }
        // Free current node
        free(temp);
        // We have freed the current node and there is nowhere to go down
        return;
    }

    // Handaling idList: It is kind of special case for non terminals with single term recurssion
    // because here idList has compulsion of atlease one child
    if ((**tree).data.name == idList) {
        parseTreeNode * temp;
        // If the right is null just make the left half king
        // Else add the left half to the right half
        if ((**tree).children[1] != NULL) {
            (**tree).children[0]->right = (**tree).children[1];
            (**tree).children[1]->left  = (**tree).children[0];
        }
        temp = *tree;
        (**tree).children[0]->parent = (**tree).parent;
        *tree = (**tree).children[0];
        free(temp);
    }


    // Remove the single term recursion cases
    if (isDoubleTermRecursionNonTerminal((**tree).data.name) == 1) {
        parseTreeNode * listPointer, * temp;
        temp = *tree;
        // Clean up the parent
        // Clean up child pointer array
        removeNullChildren(&(temp->parent));
        // Maybe the parent is not of the same type
        if (temp->parent->data.name != temp->data.name) {
            // Handle later
            // Beacuse sometime there might not exist the recursive node
        } else {
            // Attach the current node to the right of the list
            temp->parent->right = temp;
            temp->left = temp->parent;
            // Nullify the pointer to current node
            temp->parent->children[2] = NULL;
        }
    }

    // When we reach parent combine to first values in new node
    if ((**tree).data.name == caseStmts ||
      (**tree).data.name == input_plist ||
      (**tree).data.name == output_plist)
    {
        // Make a new node
        parseTreeNode * newNode;
        newNode         = (parseTreeNode *) malloc(sizeof(parseTreeNode));
        newNode->left   = NULL;
        newNode->right  = NULL;
        newNode->parent = *tree;
        for (i = 0; i < 20; ++i) {
            newNode->children[i] = NULL;
        }
        // Find which one of the parents child is this node
        i = 0;
        while ((**tree).children[i] != NULL &&
          isDoubleTermRecursionNonTerminal((**tree).children[i]->data.name) == -1)
        {
            // Make the right pointer
            newNode->children[i]         = (**tree).children[i];
            (**tree).children[i]->parent = newNode;
            (**tree).children[i]         = NULL;
            i++;
        }
        // Check if the node we reached has the recursive part
        if ((**tree).children[i] != NULL &&
          isDoubleTermRecursionNonTerminal((**tree).children[i]->data.name) == 1)
        {
            // We reached the recursive node
            newNode->data.name         = (**tree).children[i]->data.name;
            newNode->right             = (**tree).children[i];
            (**tree).children[i]->left = newNode;
            (**tree).children[i]       = NULL;
        } else {
            // A bit of hard coding :(
            if ((**tree).data.name == caseStmts) {
                newNode->data.name = N9;
            } else if ((**tree).data.name == input_plist) {
                newNode->data.name = N1;
            } else {
                newNode->data.name = N2;
            }
            strcpy(newNode->data.string, "\0");
        }

        removeNullChildren(tree);

        // Attach to parent
        (**tree).children[0] = newNode;
    }


    // For shifting the ops up
    if ((**tree).data.name == N4 || (**tree).data.name == N5 ||
      (**tree).data.name == N7 || (**tree).data.name == N8)
    {
        int i = 0;
        parseTreeNode * temp;
        temp = *tree;
        token parentName = (**tree).parent->data.name;
        // If we have not reached to the end of the recurssion
        if (temp->parent->data.name == temp->data.name) {
            temp->children[0]->parent         = temp->parent;
            temp->children[0]->children[0]    = temp->parent->children[1];
            temp->parent->children[1]->parent = temp->children[0];
            temp->children[0]->children[1]    = temp->children[1];
            temp->children[1]->parent         = temp->children[0];
            temp->parent->children[1]         = temp->children[0];
            temp->parent->children[2]         = NULL;
            *tree = temp->parent->children[1];
            free(temp);
            // End if recursion
        } else {
            temp->children[0]->parent         = temp->parent->parent;
            temp->children[0]->children[0]    = temp->parent->children[0];
            temp->parent->children[0]->parent = temp->children[0];
            temp->children[0]->children[1]    = temp->children[1];
            temp->children[1]->parent         = temp->children[0];
            *tree = temp->children[0];
            i     = 0;
            while ((**tree).parent->children[i] != NULL && (**tree).parent->children[i]->data.name != parentName) {
                i++;
            }
            (**tree).parent->children[i] = *tree;
            free(temp->parent);
            free(temp);
        }
    }

    if ((**tree).data.name == AnyTerm || (**tree).data.name == term ||
      (**tree).data.name == factor || (**tree).data.name == arithmeticExpr ||
      (**tree).data.name == arithmeticOrBooleanExpr)
    {
        int i = 0;
        parseTreeNode * temp = (**tree).children[0];
        (**tree).children[0]->parent = (**tree).parent;
        while ((**tree).parent->children[i] != (**tree).parent) {
            i++;
        }
        (**tree).parent->children[i] = (**tree).children[0];
        *tree = temp;
    }

    removeNullChildren(tree);
} /* createAST */
