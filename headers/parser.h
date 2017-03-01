// Definations for all util functions
#ifndef PARSER
#define PARSER

// Read grammer.txt to right data-structure
void readGrammer(const char *filename, grammer g);

// Read first.txt and follow.txt to right data-structure
void readFirstAndFollow(const char *first_file, const char *follow_file, non_terminals nt);

// Finds first of a set of tokens
void findFirst(token *rhs, non_terminals nt, token *first, int index);

// Makes parse table
void creatParseTable(char * grammerFile, char * firstFile, char * followFile, parse_table pt);

// Makes parse tree
void creatParseTree(parse_table pt, tree t, Token *input);

#endif // PARSER
