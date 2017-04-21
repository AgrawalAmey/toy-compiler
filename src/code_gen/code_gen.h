// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P

// Definations for all AST function defs
#ifndef CODEGEN
#define CODEGEN

void
addVaribleDefs(STTNode ** root, char * buffer);

char *
printVaribleDefs(hashTable * ht, int scopeId, char * buffer);

void
genarateCode(parseTreeNode ** t, STTNode ** sT);

void
genarateCodeRecurssively(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count);

void
addIOStmt(parseTreeNode ** t, STTNode ** sT, char * buffer);

void
addAssignStmt(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count);

void
addItrStmt(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count);

void
addCondStmt(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count);

void
addExpression(parseTreeNode ** t, STTNode ** sT, char * buffer, int * lable_count);
#endif // CODEGEN
