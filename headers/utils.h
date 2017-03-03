// Definations for all util functions
#ifndef UTILS
#define UTILS


// Convert a string to currusponding token enum
token string_to_token(const char *str);

// Returns string from token enum
const char * token_to_string(token tok);

// Convert a string to currusponding token enum
token string_to_keyword(const char *str);

// String to original symbol
const char * token_to_symbol(token tok);

// Stack functions
stackNode* createNode(token data);

// push
void push(token data, stackNode** root);

// pop
token pop(stackNode** root);

// to check if stack is empty
int isStackEmpty(stackNode** root);

// Top of the stack
token top(stackNode** root);


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
