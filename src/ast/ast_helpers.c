#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "../utils/utils.h"
#include "./ast.h"


int
isImportantTerminal(token tok)
{
    int i = 0;
    // these are not to be removed
    token verify[25] = { ARRAY, BOOLEAN,   INTEGER,
                         REAL,  GET_VALUE, PRINT,  FOR,    WHILE,
                         AND,   OR,        ID,     MINUS,  PLUS, DIV, MUL,   NUM, RNUM,
                         EQ,    GE,        GT,     LE,     LT,   NE,  FALSE, TRUE };

    for (i = 0; i < 25; i++) {
        // Is important
        if (verify[i] == tok || tok < 1000) {
            return 1;
        }
    }

    return -1;
}

int
isRedundentNonTerminal(token tok)
{
    int i = 0;
    // these are not to be removed
    token verify[15] = { moduleDeclaration, ret,        type,      statement,
                         whichId,           simpleStmt, whichStmt, INDEX,
                         factor,            op1,        op2,       logicalOp,
                         relationalOp,      value,      default_nt };

    for (i = 0; i < 15; i++) {
        // Is redunndent
        if (verify[i] == tok) {
            return 1;
        }
    }

    return -1;
}

int
isSingleTermRecursionNonTerminal(token tok)
{
    int i = 0;
    // these are not to be removed
    token verify[4] = { N3, statements, otherModules, moduleDeclarations };

    for (i = 0; i < 4; i++) {
        // Is Single Term Recursion Non-Terminal
        if (verify[i] == tok) {
            return 1;
        }
    }

    return -1;
}

int
isDoubleTermRecursionNonTerminal(token tok)
{
    int i = 0;
    // these are not to be removed
    token verify[3] = { N1, N2, N9 };

    for (i = 0; i < 3; i++) {
        // Is Single Term Recursion Non-Terminal
        if (verify[i] == tok) {
            return 1;
        }
    }

    return -1;
}

void
removeNullChildren(parseTreeNode ** root)
{
    int i, j;

    for (j = 0; j < 20; ++j) {
        for (i = j; i < 19; ++i) {
            if ((**root).children[i] == NULL) {
                (**root).children[i]     = (**root).children[i + 1];
                (**root).children[i + 1] = NULL;
            }
        }
    }
}

void
printASTPostOrder(parseTreeNode ** tree)
{
    int i;

    if (*tree == NULL) {
        return;
    }
    // Try to go right ways
    printASTPostOrder(&((**tree).right));
    // Recurese
    for (i = 0; i < 20; i++) {
        printASTPostOrder(&((**tree).children[i]));
    }
    if ((**tree).parent == NULL) {
        printf("Name: %s\nString:%s\nScope:%d\n",
          token_to_string((**tree).data.name), (**tree).data.string, (**tree).scopeId);
    } else if ((**tree).left != NULL) {
        printf("Name: %s\nString:%s\nLeft:%s\nScope:%d\n",
          token_to_string((**tree).data.name), (**tree).data.string,
          token_to_string((**tree).left->data.name), (**tree).scopeId);
    } else {
        printf("Name: %s\nString:%s\nParent:%s\nScope:%d\n",
          token_to_string((**tree).data.name), (**tree).data.string,
          token_to_string((**tree).parent->data.name), (**tree).scopeId);
    }
    printf("----------------------------------\n");
}
