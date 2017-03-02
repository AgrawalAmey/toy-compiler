// Definations for all util functions
#ifndef PARSER
#define PARSER

// Read grammer.txt to right data-structure
void readGrammer(const char *filename, grammer g);

// Read first.txt and follow.txt to right data-structure
void readFirstAndFollow(const char *first_file, const char *follow_file, non_terminals nt);

// Finds first of a set of tokens
int findFirstRecursive(token *rhs, non_terminals nt, token *first, int index);

// Create first and follow
void findFirstAndFollow(grammer g, non_terminals nt);

// Find first (to be called by findFirstAndFollow)
int findFirst(token tok, token *rhs, non_terminals nt, int index);

// Find follow (to be called by findFirstAndFollow)
int findFollow(token tok, token lhs, token *rhs, non_terminals nt, int index, int hasEpsilonLast);

// Makes parse table
void creatParseTable(char * grammerFile, char * firstFile, char * followFile, parse_table pt);

// Makes parse tree
void creatParseTree(parse_table pt, tree t, Token *input);

#endif // PARSER
