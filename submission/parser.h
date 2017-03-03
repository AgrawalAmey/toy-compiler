// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P

// Definations for all parser functions
#ifndef PARSER
#define PARSER

// Read grammer.txt to right data-structure
int readGrammer(const char *filename, grammer g);

// Read first.txt and follow.txt to right data-structure
void readFirstAndFollow(const char *first_file, const char *follow_file, non_terminals nt);

// Finds first of a set of tokens
int findFirstRecursive(token *rhs, non_terminals nt, token *first, int index);

// Create first and follow
void findFirstAndFollow(grammer g, non_terminals nt);

// Find first (to be called by findFirstAndFollow)
int findFirst(token tok, token *rhs, non_terminals nt, int index);

// Find follow (to be called by findFirstAndFollow)
int findFollow(token tok, token lhs, token *rhs, non_terminals nt, int index);

// Makes parse table
void creatParseTable(char * grammerFile, parse_table pt);

// Makes parse tree
int creatParseTree(parse_table pt, tree t, Token *input);

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
void printTreeToFile(FILE* fp, treeNode ** tree);


#endif // PARSER
