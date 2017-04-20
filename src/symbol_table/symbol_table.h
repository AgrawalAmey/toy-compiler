// Definations for all symbol table functions
#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

void populateSymbolTable(parseTree pT, symbolTableTree sT, hashTable * fT);

int insertEntryInSTT(char * key, tableEntry data, int scopeId, STTNode ** root);

// Insert an entry in symbol table
int insertEntryInFT(char * key, tableEntry data, hashTable * fT);

STTNode ** createSTT();

// Inserts node as children to given node
int insertInSTT(char * name, int parentScopeId, STTNode ** root);

// Add a node to given parent
void insertSTTNode(char * name, int scopeId, STTNode ** parent);

void printSTTInOrder(STTNode ** root);

// Get an entry in symbol table
int getEntryFromSTT(char * key, tableEntry * data, int scopeId, STTNode ** root);

// Get an entry in symbol table
int getEntryFromFT(char * key, tableEntry * data, hashTable * fT);

#endif // SYMBOL_TABLE
