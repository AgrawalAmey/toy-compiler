#include <stdlib.h>
#include <stdio.h>
#include "../custom_types/token.h"
#include "../custom_types/structs.h"
#include "../headers/utils.h"

treeNode ** createTree(){
   treeNode ** root;
   root = (treeNode **)malloc(sizeof(treeNode *));
   *root = NULL;
   return root;
}

// Inserts nodes as children to given node
void insertTreeNodes(token *vals, treeNode ** root){
    int i = 0;
    int j = 0;

    // Assumes that the node has no children initially
    while (vals[i] != 0) {

        treeNode * temp;
        temp = (treeNode *)malloc(sizeof(treeNode));
        // We have set maximum number of children at 10
        for(j=0; j<20; j++){
            temp->children[j] = NULL;
        }

        temp->associated = 0;
        temp->data.name = vals[i];
        temp->parent = *root;

        // For root node insertion
        if(*root == NULL){
            *root = temp;
            return;
        } else{
            // Update child pointer of parent
            (**root).children[i] = temp;
        }

        i++;
    }
}

// Insert nodes into tree
int insertInTree(token * vals, treeNode ** tree){
    int i = 0;

    // If empty node
    if((*tree) == NULL){
        insertTreeNodes(vals, tree);
        return 1;
    // For non-terminal nodes
    } else if((**tree).data.name < 1000){
        if((**tree).children[0] == NULL){
            // Child does not exist so insert here
            insertTreeNodes(vals, tree);
            return 1;
        }
        // Try to insert at the left-most children
        for(i=0; i<20; i++){
            if((**tree).children[i] != NULL){
                if(insertInTree(vals, &((**tree).children[i]))){
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

int insertLeafData(Token t, treeNode **tree){
    int i;
    // Should never be called before tree is made
    if(*tree != NULL){
        // Base case: if node is a terminal and unassigned
        if((**tree).data.name >= 1000 && (**tree).data.name != EPSILON && !(**tree).associated){
            (**tree).data = t;
            (**tree).associated = 1;
            return 1;
        } else {
            // Try to insert into children
            for(i=0; i<20; i++){
                if((**tree).children[i] != NULL){
                    if(insertLeafData(t, &((**tree).children[i]))){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
}

void printInorder(treeNode **tree){
    int i;

    if(*tree != NULL){
        printInorder(&((**tree).children[0]));
        // If is a terminal or leaf in other words
        if((**tree).data.name >= 1000 && (**tree).data.name != EPSILON){
            printf("| %25s | %25d | %25s | %25s | %25s | %25s | %25s |\n\n", (**tree).data.string, (**tree).data.line_number,
                token_to_string((**tree).data.name), (**tree).data.string, "yes",
                token_to_string((*(**tree).parent).data.name), token_to_symbol((**tree).data.name));
        } else {
            // If parent is null (Only possible with with non-terminal root)
            if((**tree).parent == NULL){
                printf("| %25s | %25s | %25s | %25s | %25s | %25s | %25s |\n\n", "---", "---", token_to_string((**tree).data.name), "---", "no", "ROOT", token_to_string((**tree).data.name));
            } else {
                printf("| %25s | %25s | %25s | %25s | %25s | %25s | %25s |\n\n",
                    "---", "---", token_to_string((**tree).data.name), "---", "no",
                    token_to_string((*(**tree).parent).data.name), token_to_string((**tree).data.name));
            }
        }

        for(i=1; i<20; i++){
            printInorder(&((**tree).children[i]));
        }
    }
}
