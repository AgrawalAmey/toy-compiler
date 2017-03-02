// Definations for all lexer functions
#ifndef LEXSER
#define LEXSER

int isSpace(char ch);

int isNewLine(char ch);

int isAlphabet(char ch);

int isDigit(char ch);

Token createToken(char * lex,int l,Token tok);

FILE* getStream(FILE *fp,char *buffer,int size);

char * fetch_or_not(FILE* fp,char * buffer,int flag,int size);

Token getNextToken(FILE* fp,char* buffer,int size);

void removeComments(char *testcaseFile,char *cleanFile);

Token* getTokens(const char* filename,Token* tokenArray);


#endif // LEXSER
