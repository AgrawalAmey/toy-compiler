// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P

// Definations for all lexer functions
#ifndef LEXER
#define LEXER

int isSpace(char ch);

int isNewLine(char ch);

int isAlphabet(char ch);

int isDigit(char ch);

Token createToken(char * lex,int l);

FILE* getStream(FILE *fp, char *buffer, int offset);

void removeComments(char *testcaseFile,char *cleanFile);

int getTokens(const char* filename,Token* tokenArray);

// Convert a string to currusponding token enum
token string_to_token(const char *str);

// Returns string from token enum
const char * token_to_string(token tok);

// Convert a string to currusponding token enum
token string_to_keyword(const char *str);

// String to original symbol
const char * token_to_symbol(token tok);

#define SIZE 4000

#endif // LEXER
