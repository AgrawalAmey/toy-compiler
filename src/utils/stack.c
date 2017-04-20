#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./utils.h"

stackNode *
createNode(token data)
{
    stackNode * node = (stackNode *) malloc(sizeof(stackNode));

    node->data = data;
    node->next = NULL;
    return node;
}

int
isStackEmpty(stackNode ** root)
{
    return !(*root);
}

void
push(token data, stackNode ** root)
{
    stackNode * node = createNode(data);

    node->next = *root;
    *root      = node;
}

token
pop(stackNode ** root)
{
    if (isStackEmpty(root))
        return -1;

    stackNode * temp = *root;
    *root = (*root)->next;
    token popped = temp->data;
    free(temp);

    return popped;
}

token
top(stackNode ** root)
{
    if (isStackEmpty(root))
        return -1;

    return (*root)->data;
}
