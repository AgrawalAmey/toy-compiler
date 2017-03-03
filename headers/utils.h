// Definations for all util functions
#ifndef UTILS
#define UTILS


// Convert a string to currusponding token enum
token string_to_token(const char *str);

// Returns string from token enum
const char * token_to_string(token tok);

// Convert a string to currusponding token enum
token string_to_keyword(const char *str);

// Stack functions

// creates empty stack
stack createStack();

// push
void push(token data, stack s);

// pop
token pop(stack s);

// to check if stack is empty
int isStackEmpty(stack s);

// To print stack
void printStack(stack s);


// Tree functions

// create empty tree
treeNode ** createTree();

// Insert array of value in tree
int insertInTree(token * vals, treeNode ** tree);

// Insert data into leaf nodes
int insertLeafData(Token t, treeNode **tree);

// Print tree in-order
void printInorder(treeNode ** tree);

#endif // UTILS
