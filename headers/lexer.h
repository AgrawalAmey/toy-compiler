// Definations for all lexer functions
#ifndef LEXSER
#define LEXSER

int isSpace(char ch);

int isNewLine(char ch);

int isAlphabet(char ch);

int isDigit(char ch);

Token createToken(char * lex,int l);

FILE* getStream(FILE *fp, char *buffer, int offset);

void removeComments(char *testcaseFile,char *cleanFile);

int getTokens(const char* filename,Token* tokenArray);

#define SIZE 4000

#endif // LEXSER
