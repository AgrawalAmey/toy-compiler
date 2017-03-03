// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./lexerDef.h"
#include "./lexer.h"
#include "./parserDef.h"
#include "./parser.h"


void creatParseTable(char * grammerFile, parse_table pt){
    int i, j, k;
    grammer g;
    non_terminals nt;
    token first[30];
    int hasEpsilon = 0;

    // This needs to be defined here because possition of these files respect to
    // caller fuction may be different
    readGrammer(grammerFile, g);

    findFirstAndFollow(g, nt);

    // Zero initialization
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            for (k = 0; k < 20; k++) {
                pt[i][j][k] = 0;
            }
        }
    }

    i = j = k = 0;

    while (g[i].lhs != 0){

        // Reset first
        for (j = 0; j < 30; j++) {
            first[j] = 0;
        }

        // Get the first set for rhs
        findFirstRecursive(g[i].rhs, nt, first, 0);

        // The three cases

        // Iterate over first set
        j = 0;
        while (first[j] != 0) {
            // Copy rhs to appropriate place
            memcpy(pt[g[i].lhs-500][first[j]-1000], g[i].rhs, 20 * sizeof(token));

            // Check if terminal is EPSILON
            if(first[j] == EPSILON)
                hasEpsilon = 1;

            j++;
        }

        // If epsilon is in first of rhs consider follow of A
        if (hasEpsilon){
            j = 0;
            while (nt[g[i].lhs-500].follow[j] != 0) {
                // Copy rhs to appropriate place
                memcpy(pt[g[i].lhs-500][nt[g[i].lhs-500].follow[j]-1000], g[i].rhs, 20 * sizeof(token));

                j++;
            }
        }

        // Reset flags
        hasEpsilon = 0;

        i++;
    }
}

int creatParseTree(parse_table pt, tree t, Token *input){
    // Initialize stack
    stackNode* s = NULL;
    push(eof, &s);
    push(program, &s);

    // Initialize tree
    token __program[1] = { program };
    insertInTree(__program, t);

    int readHead = 0;
    token tok;
    int i = 0;
    int j;

    while(isStackEmpty(&s) != 1){
        tok = pop(&s);
        // Index of terminals start from 1000
        // Top of stack is terminal
        if (tok >= 1000){
            // Terminals match
            if(tok == input[readHead].name){
                insertLeafData(input[readHead], t);
                readHead++;
            } else {
                // Terminal match failed
                printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is %s.\n",
                token_to_string(input[readHead].name), input[readHead].string, input[readHead].line_number, token_to_symbol(tok));
                return -1;
            }
        } else {
            // Top of stack is non-terminal
            // There exists a table entry for incoming input
            if(pt[tok-500][input[readHead].name-1000][0] != 0){
                i = 0;
                // Find the end of rule
                while(pt[tok-500][input[readHead].name-1000][i] != 0){
                    i++;
                }

                i--;
                // Insert the rule to stack in reverse order
                while(i >= 0){
                    if(pt[tok-500][input[readHead].name-1000][i] != EPSILON){
                        push(pt[tok-500][input[readHead].name-1000][i], &s);
                    }
                    i--;
                }

                // Insert into tree
                insertInTree(pt[tok-500][input[readHead].name-1000], t);

            } else {
                // There is not entry in the table
                // If the rule has an entry for epsilon
                if(pt[tok-500][EPSILON-1000][0] != 0){
                    // pass
                } else {
                    printf("%d\n", pt[tok-500][EPSILON][0]);
                    printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is ",
                    token_to_string(input[readHead].name), input[readHead].string, input[readHead].line_number);
                    for (j = 0; j < 100; j++) {
                        if (pt[tok-500][j][0] != 0 && pt[tok-500][j][0] != EPSILON) {
                            printf("%s ", token_to_symbol(j+1000));
                        }
                    }
                    printf(".\n");
                    return -1;
                }
            }
        }
    }

    return 0;
}

void findFirstAndFollow(grammer g, non_terminals nt){
    int i, j, k = 0;
    int first_indexs[100] = { 0 };
    int follow_indexs[100] = { 0 };
    int total = 0;
    int last_index, last_total;
    token tok;

    // Initialize everything with zeros
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 20; j++) {
            nt[i].first[j] = 0;
            nt[i].follow[j] = 0;
        }
    }

    i = j = k = 0;

    // For first
    do{
        i = 0;
        last_total = total;

        while(g[i].lhs != 0) {
            // Count before the itration
            last_index = first_indexs[g[i].lhs-500];
            // Add new terms
            first_indexs[g[i].lhs-500] = findFirst(g[i].lhs, g[i].rhs, nt, first_indexs[g[i].lhs-500]);
            // Add the difference to total
            total = total + first_indexs[g[i].lhs-500] - last_index;

            i++;
        }

    } while(total != last_total);

    // Reset variable
    total = last_total = 0;

    // Add eof
    nt[program-500].follow[0] = eof;
    follow_indexs[program-500]++;

    // For follow
    do{
        i = 0;
        last_total = total;
        // For all symbols
        while(g[i].lhs != 0){
            j = 0;
            tok = g[i].lhs;
            // For all rules
            while(g[j].lhs != 0){
                k = 0;

                // Count before the itration
                last_index = follow_indexs[tok-500];

                // Find the position of rhs
                while(g[j].rhs[k] != 0) {
                    if(g[j].rhs[k] == tok){
                        // Add new terms
                        follow_indexs[tok-500] = findFollow(tok, g[j].lhs, g[j].rhs+k+1, nt, follow_indexs[tok-500]);
                        // Add the difference to total
                        total = total + follow_indexs[tok-500] - last_index;

                        break;
                    }
                    k++;
                }

                j++;
            }
            i++;
        }

    } while(total != last_total);
}


// Finds first of rhs of a rule recursively
int findFirstRecursive(token *rhs, non_terminals nt, token *first, int index){
    int i = 0;
    // Flag
    int hasEpsilon = 0;

    if (rhs[0] == 0){
        return index;
    }

    // Index of terminals start from 1000
    // Terminal Case
    if (rhs[0] >= 1000){
        first[index] = rhs[0];

        // Check if terminal is EPSILON
        if(rhs[0] == EPSILON)
            hasEpsilon = 1;

        index++;
    } else {
        // Non-terminal case
        while (nt[rhs[0]-500].first[i] != 0){
            first[index] = nt[rhs[0]-500].first[i] ;

            // Flag is set to true if epsilon is in the first of non_terminal
            if (nt[rhs[0]-500].first[i] == EPSILON)
                hasEpsilon = 1;

            i++;
            index++;
        }
    }
    // Make recursive call
    if (hasEpsilon){
        findFirstRecursive(rhs+1, nt, first, index);
    }
    return index;
}


// Finds first of rhs of a rule recursively
int findFirst(token tok, token *rhs, non_terminals nt, int index){

    int i = 0;
    int j = 0;
    // Flag
    int hasEpsilon = 0;
    int ifExists = 0;

    if (rhs[0] == 0){
        while(nt[tok-500].first[j] != 0){
            if (nt[tok-500].first[j] == EPSILON) {
                return index;
            }
            j++;
        }
        return index;
    }

    // Index of terminals start from 1000
    // Terminal Case
    if (rhs[0] >= 1000){
        j = 0;
        // Check if it already exists
        while(nt[tok-500].first[j] != 0){
            if (nt[tok-500].first[j] == rhs[0]) {
                return index;
            }
            j++;
        }

        nt[tok-500].first[index] = rhs[0];

        // Check if terminal is EPSILON
        if(rhs[0] == EPSILON)
            hasEpsilon = 1;

        index++;
    } else {
        // Non-terminal case
        while (nt[rhs[0]-500].first[i] != 0){

            ifExists = 0;
            j = 0;

            // Check if it already exists
            while(nt[tok-500].first[j] != 0){
                if (nt[tok-500].first[j] == nt[rhs[0]-500].first[i]) {
                    ifExists = 1;
                }
                j++;
            }

            if(!ifExists && nt[rhs[0]-500].first[i] != EPSILON){
                nt[tok-500].first[index] = nt[rhs[0]-500].first[i];
                index++;
            }

            // Flag is set to true if epsilon is in the first of non_terminal
            if (nt[rhs[0]-500].first[i] == EPSILON)
                hasEpsilon = 1;

            i++;
        }
    }
    // Make recursive call
    if (hasEpsilon){
        findFirst(tok, rhs+1, nt, index);
    }
    return index;
}


// Finds follow of rhs of a rule recursively
int findFollow(token tok, token lhs, token *rhs, non_terminals nt, int index){

    int i = 0;
    int j = 0;

    // Flag
    int ifExists = 0;
    int hasEpsilon = 0;

    // Possible only if tok is the right-most or everything on right can derive epsilon
    if (rhs[0] == 0){
        while (nt[lhs-500].follow[i] != 0){

            j = 0;
            ifExists = 0;

            // Check if it already exists
            while(nt[tok-500].follow[j] != 0){
                if (nt[tok-500].follow[j] == nt[lhs-500].follow[i]) {
                    ifExists = 1;
                }
                j++;
            }

            if(!ifExists && nt[lhs-500].follow[i] != EPSILON){
                nt[tok-500].follow[index] = nt[lhs-500].follow[i] ;
                index++;
            }

            i++;
        }
        return index;
    }

    // Index of terminals start from 1000
    // Terminal Case
    if (rhs[0] >= 1000 && rhs[0] != EPSILON){

        j = 0;
        // Check if it already exists
        while(nt[tok-500].follow[j] != 0){
            if (nt[tok-500].follow[j] == rhs[0]) {
                return index;
            }
            j++;
        }

        if(rhs[0] != EPSILON){
            nt[tok-500].follow[index] = rhs[0];
            index++;
        } else {
            hasEpsilon = 1;
        }

    } else {
        // Non-terminal case
        while (nt[rhs[0]-500].first[i] != 0){

            j = 0;
            ifExists = 0;

            // Check if it already exists
            while(nt[tok-500].follow[j] != 0){
                if (nt[tok-500].follow[j] ==  nt[rhs[0]-500].first[i]) {
                    ifExists = 1;
                }
                j++;
            }

            if(!ifExists && nt[rhs[0]-500].first[i] != EPSILON){
                nt[tok-500].follow[index] = nt[rhs[0]-500].first[i];
                index++;
            }

            // Flag is set to true if epsilon is in the follow of non_terminal
            if (nt[rhs[0]-500].first[i] == EPSILON)
                hasEpsilon = 1;

            i++;
        }
    }
    // Make recursive call
    if (hasEpsilon){
        findFollow(tok, lhs, rhs+1, nt, index);
    }

    return index;
}

int readGrammer(const char *filename, grammer g){

    int i, j;
    FILE *f = fopen(filename, "rt");
    if (f == NULL){
        printf("Grammer File does not exist.\n");
        return -1;
    }
    // Tokens are no longer
    char buffer[50];
    char ch;

    int row_num = 0;
    int word_num = 0;

    // Initialize everything with zeros
    for (i = 0; i < 100; i++) {
        g[i].lhs = 0;
        for (j = 0; j < 20; j++) {
            g[i].rhs[j] = 0;
        }
    }

    while (fscanf(f, "%s%c", buffer, &ch) == 2){

        if (word_num == 0){
            g[row_num].lhs = string_to_token(buffer);
        } else {
            g[row_num].rhs[word_num-1] = string_to_token(buffer);
        }

        // Essential for lhs and rhs
        word_num++;

        // Take care of line number
        if (ch == '\n'){
            row_num++;
            word_num = 0;
        }
    }

    fclose(f);
}


stackNode* createNode(token data){
    stackNode* node = (stackNode*) malloc(sizeof(stackNode));
    node->data = data;
    node->next = NULL;
    return node;
}

int isStackEmpty(stackNode** root){
    return !(*root);
}

void push(token data, stackNode** root){
    stackNode* node = createNode(data);
    node->next = *root;
    *root = node;
}

token pop(stackNode** root){
    if (isStackEmpty(root))
        return -1;
    stackNode* temp = *root;
    *root = (*root)->next;
    token popped = temp->data;
    free(temp);

    return popped;
}

token top(stackNode** root){
    if (isStackEmpty(root))
        return -1;
    return (*root)->data;
}

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

void printTreeToFile(FILE * fp, treeNode **tree){
    int i;

    if(*tree != NULL){
        printTreeToFile(fp, &((**tree).children[0]));
        // If is a terminal or leaf in other words
        if((**tree).data.name >= 1000 && (**tree).data.name != EPSILON){
            fprintf(fp, "| %25s | %25d | %25s | %25s | %25s | %25s | %25s |\n\n", (**tree).data.string, (**tree).data.line_number,
                token_to_string((**tree).data.name), (**tree).data.string, "yes",
                token_to_string((*(**tree).parent).data.name), token_to_symbol((**tree).data.name));
        } else {
            // If parent is null (Only possible with with non-terminal root)
            if((**tree).parent == NULL){
                fprintf(fp, "| %25s | %25s | %25s | %25s | %25s | %25s | %25s |\n\n", "---", "---", token_to_string((**tree).data.name), "---", "no", "ROOT", token_to_string((**tree).data.name));
            } else {
                fprintf(fp, "| %25s | %25s | %25s | %25s | %25s | %25s | %25s |\n\n",
                    "---", "---", token_to_string((**tree).data.name), "---", "no",
                    token_to_string((*(**tree).parent).data.name), token_to_string((**tree).data.name));
            }
        }

        for(i=1; i<20; i++){
            printTreeToFile(fp, &((**tree).children[i]));
        }
    }
}
