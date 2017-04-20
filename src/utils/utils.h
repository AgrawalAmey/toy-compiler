// Definations for all util functions
#ifndef UTILS
#define UTILS


// Convert a string to currusponding token enum
token string_to_token(char *str);

// Returns string from token enum
char * token_to_string(token tok);

// Convert a string to currusponding token enum
token string_to_keyword(char *str);

// String to original symbol
char * token_to_symbol(token tok);

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

// Hash table functions
// Create hashTable
hashTable *createHashtable();

// Hash string
int getHash(hashTable *ht, char *key);

hashTableEntry * createHashtablePair(char * key, tableEntry data);

int insertInHashtable(hashTable * ht, char * key, tableEntry data, int mode);

// Find a pair
int findInHashtable(hashTable * ht, char * key, tableEntry * data);

// Print hash table
char * printHashtable(hashTable * ht);

#endif // UTILS
