// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P

// Definations for all AST function defs
#ifndef ASTDEF
#define ASTDEF

int isImportantTerminal(token tok);

int isRedundentNonTerminal(token tok);

int isSingleTermRecursionNonTerminal(token tok);

int isDoubleTermRecursionNonTerminal(token tok);

void removeNullChildren(parseTreeNode ** root);

void createAST(parseTreeNode ** tree);

void printASTPostOrder(parseTreeNode ** tree);

#endif // ASTDEF
