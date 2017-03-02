// Definations for all lexer functions
#ifndef LEXSER
#define LEXSER

int isSpace(char ch);


int isNewLine(char ch);

int isAlphabet(char ch);

int isDigit(char ch);

tokenInfo getToken(char * lex,int l,tokenInfo tok);

FILE* getStream(FILE *fp,char *buffer,int size);

tokenInfo getNextToken(FILE* fp,char* buffer,int size);

void removeComments(char *testcaseFile,char *cleanFile);

tokenInfo* getTokens(const char* filename,tokenInfo* tokenArray);


#endif // LEXSER
