// Definations for all parser functions
#ifndef PARSER
#define PARSER

// Read grammer.txt to right data-structure
int readGrammer(char *filename, grammer g);

// Read first.txt and follow.txt to right data-structure
void readFirstAndFollow(char *first_file, char *follow_file, non_terminals nt);

// Finds first of a set of tokens
int findFirstRecursive(token *rhs, non_terminals nt, token *first, int index);

// Create first and follow
void findFirstAndFollow(grammer g, non_terminals nt);

// Find first (to be called by findFirstAndFollow)
int findFirst(token tok, token *rhs, non_terminals nt, int index);

// Find follow (to be called by findFirstAndFollow)
int findFollow(token tok, token lhs, token *rhs, non_terminals nt, int index);

// Tree functions
// create empty tree
parseTreeNode ** createEmptyParseTree();

// Insert array of value in tree
int insertInParseTree(token * vals, parseTreeNode ** tree);

// Insert data into leaf nodes
int insertLeafDataInParseTree(Token t, parseTreeNode **tree);

// Print tree in-order
void printParseTreeInorder(parseTreeNode ** tree);

// Makes parse table
void createParseTable(char * grammerFile, parse_table pt);

// Makes parse tree
int createParseTree(parse_table pt, parseTree t, Token *input);

void
countNodes(parseTreeNode ** tree, int * num);


#endif // PARSER
