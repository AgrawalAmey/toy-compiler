// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./lexerDef.h"
#include "./lexer.h"

// Kind of look-up table to convert string to corrosponding enum
const static struct {
    token val;
    const char *str;
} symbol_conversions[] = {
    // keywords: A subset of tokens
    { AND, "AND" },
	{ ARRAY, "array" },
	{ ASSIGNOP, ":=" },
	{ BC, ")" },
	{ BO, "(" },
	{ BOOLEAN, "boolean" },
	{ BREAK, "break" },
	{ CASE, "case" },
	{ COLON, ":" },
	{ COMMA, "," },
	{ DECLARE, "declare" },
	{ DEF, "def" },
	{ DEFAULT, "default" },
	{ DIV, "/" },
	{ DRIVER, "driver" },
	{ DRIVERDEF, "<<<" },
	{ DRIVERENDDEF, ">>>" },
	{ END, "end" },
	{ ENDDEF, ">>" },
	{ EQ, "==" },
	{ FALSE, "false" },
	{ FOR, "for" },
	{ GE, ">=" },
	{ GET_VALUE, "get_value" },
	{ GT, ">" },
	{ ID, "ID" },
	{ IN, "in" },
	{ INPUT, "input" },
	{ INTEGER, "integer" },
	{ LE, "<=" },
	{ LT, "<" },
	{ MINUS, "minus" },
	{ MODULE, "module" },
	{ MUL, "*" },
	{ NE, "!=" },
	{ NUM, "NUM" },
	{ OF, "of" },
	{ OR, "OR" },
	{ PARAMETERS, "parameters" },
	{ PLUS, "+" },
	{ PRINT, "print" },
    { PROGRAM, "program" },
    { RANGEOP, ".." },
    { REAL, "real" },
    { RETURNS, "returns" },
    { RNUM, "RNUM" },
    { SEMICOL, ";" },
    { SQBC, "]" },
    { SQBO, "[" },
    { START, "start" },
    { SWITCH, "switch" },
    { TAKES, "takes" },
    { TRUE, "true" },
    { USE, "use" },
    { WHILE, "while" },
    { WITH, "with" }
};

// Returns string from token enum
const char * token_to_symbol(token tok){
     int i;
     for (i = 0;  i < sizeof (symbol_conversions) / sizeof (symbol_conversions[0]);  i++){
         if (tok == symbol_conversions[i].val)
             return symbol_conversions[i].str;
     }
     printf("Invalid token: %d.\n", tok);
}


// Kind of look-up table to convert string to corrosponding enum
const static struct {
    token val;
    const char *str;
} conversions[] = {
    { AnyTerm, "AnyTerm" },
    { N1, "N1" },
    { N2, "N2" },
    { N3, "N3" },
    { N4, "N4" },
    { N5, "N5" },
    { N7, "N7" },
    { N8, "N8" },
    { N9, "N9" },
    { arithmeticExpr, "arithmeticExpr" },
    { arithmeticOrBooleanExpr, "arithmeticOrBooleanExpr" },
    { assignmentStmt, "assignmentStmt" },
    { caseStmts, "caseStmts" },
    { conditionalStmt, "conditionalStmt" },
    { dataType, "dataType" },
    { declareStmt, "declareStmt" },
    { default_nt, "default" },
    { driverModule, "driverModule" },
    { expression, "expression" },
    { factor, "factor" },
    { idList, "idList" },
    { INDEX, "index" },
    { input_plist, "input_plist" },
    { ioStmt, "ioStmt" },
    { iterativeStmt, "iterativeStmt" },
    { logicalOp, "logicalOp" },
    { lvalueARRStmt, "lvalueARRStmt" },
    { lvalueIDStmt, "lvalueIDStmt" },
    { module, "module" },
    { moduleDeclaration, "moduleDeclaration" },
    { moduleDeclarations, "moduleDeclarations" },
    { moduleDef, "moduleDef" },
    { moduleReuseStmt, "moduleReuseStmt" },
    { op1, "op1" },
    { op2, "op2" },
    { optional, "optional" },
    { otherModules, "otherModules" },
    { output_plist, "output_plist" },
    { program, "program" },
    { range, "range" },
    { relationalOp, "relationalOp" },
    { ret, "ret" },
    { simpleStmt, "simpleStmt" },
    { statement, "statement" },
    { statements, "statements" },
    { term, "term" },
    { type, "type" },
    { value, "value" },
    { var, "var" },
    { whichId, "whichId" },
    { whichStmt, "whichStmt" },
    { AND, "AND" },
	{ ARRAY, "ARRAY" },
	{ ASSIGNOP, "ASSIGNOP" },
	{ BC, "BC" },
	{ BO, "BO" },
	{ BOOLEAN, "BOOLEAN" },
	{ BREAK, "BREAK" },
	{ CASE, "CASE" },
	{ COLON, "COLON" },
	{ COMMA, "COMMA" },
	{ DECLARE, "DECLARE" },
	{ DEF, "DEF" },
	{ DEFAULT, "DEFAULT" },
	{ DIV, "DIV" },
	{ DRIVER, "DRIVER" },
	{ DRIVERDEF, "DRIVERDEF" },
	{ DRIVERENDDEF, "DRIVERENDDEF" },
	{ END, "END" },
	{ ENDDEF, "ENDDEF" },
	{ EQ, "EQ" },
	{ FALSE, "FALSE" },
	{ FOR, "FOR" },
	{ GE, "GE" },
	{ GET_VALUE, "GET_VALUE" },
	{ GT, "GT" },
	{ ID, "ID" },
	{ IN, "IN" },
	{ INPUT, "INPUT" },
	{ INTEGER, "INTEGER" },
	{ LE, "LE" },
	{ LT, "LT" },
	{ MINUS, "MINUS" },
	{ MODULE, "MODULE" },
	{ MUL, "MUL" },
	{ NE, "NE" },
	{ NUM, "NUM" },
	{ OF, "OF" },
	{ OR, "OR" },
	{ PARAMETERS, "PARAMETERS" },
	{ PLUS, "PLUS" },
	{ PRINT, "PRINT" },
    { PROGRAM, "PROGRAM" },
    { RANGEOP, "RANGEOP" },
    { REAL, "REAL" },
    { RETURNS, "RETURNS" },
    { RNUM, "RNUM" },
    { SEMICOL, "SEMICOL" },
    { SQBC, "SQBC" },
    { SQBO, "SQBO" },
    { START, "START" },
    { SWITCH, "SWITCH" },
    { TAKES, "TAKES" },
    { TRUE, "TRUE" },
    { USE, "USE" },
    { WHILE, "WHILE" },
    { WITH, "WITH" },
    { COMMENTMARK, "COMMENTMARK" },
    { EPSILON, "EPSILON" },
    { eof, "EOF" }
};

// Returns token enum from string
token string_to_token(const char *str){
     int i;
     for (i = 0;  i < sizeof (conversions) / sizeof (conversions[0]);  i++){
         if (!strcmp (str, conversions[i].str))
             return conversions[i].val;
     }
     printf("Invalid token string: %s.\n", str);
}

// Returns string from token enum
const char * token_to_string(token tok){
     int i;
     for (i = 0;  i < sizeof (conversions) / sizeof (conversions[0]);  i++){
         if (tok == conversions[i].val)
             return conversions[i].str;
     }
     printf("Invalid token: %d.\n", tok);
}

// Kind of look-up table to convert string to corrosponding enum
const static struct {
    token val;
    const char *str;
} keyword_conversions[] = {
    // keywords: A subset of tokens
    { AND, "AND" },
    { ARRAY, "array" },
    { BOOLEAN, "boolean" },
    { BREAK, "break" },
    { CASE, "case" },
    { DECLARE, "declare" },
    { DEFAULT, "default" },
    { DRIVER, "driver" },
    { END, "end" },
    { FALSE, "false" },
    { FOR, "for" },
    { GET_VALUE, "get_value" },
    { IN, "in" },
    { INPUT, "input" },
    { INTEGER, "integer" },
    { MODULE, "module" },
    { OF, "of" },
    { OR, "OR" },
    { PARAMETERS, "parameters" },
    { PRINT, "print" },
    { PROGRAM, "program" },
    { REAL, "real" },
    { RETURNS, "returns" },
    { START, "start" },
    { SWITCH, "switch" },
    { TAKES, "takes" },
    { TRUE, "true" },
    { USE, "use" },
    { WHILE, "while" },
    { WITH, "with" }
};

// Returns token enum from string
token string_to_keyword(const char *str){
     int i;
     for (i = 0;  i < sizeof (keyword_conversions) / sizeof (keyword_conversions[0]);  i++){
         if (!strcmp (str, keyword_conversions[i].str))
             return keyword_conversions[i].val;
     }
     return 0;
}


Token createToken(char * lex,int l)
{
	Token tok;
	//we shall use strcmpi for insensitive case string comparison
	tok.line_number = l;
	tok.name = ID;
	strcpy(tok.string, lex);

	if(string_to_keyword(lex) != 0){
		tok.name = string_to_keyword(lex);
	}

	return tok;
}


//IMP:Checks if we have encountered '\0' in buffer
//:if yes,we fetch from file again
//checks if '\0' is encountered,and if eof not reached,I have to fetch
FILE* getStream(FILE* fp, char * buffer, int offset){
	char temp[SIZE] = { '\0' };

	if((buffer[offset] == '\0' || strlen(buffer) == 0) && !feof(fp)){
			//for fetching new stream of size of buffer
			memset(buffer, '\0', SIZE);//end should be a '\0'

			//size should be typically 200
			//as of now assumption is that a line doesnt exceed 200 limit
			fread(temp, 1, SIZE-1, fp);

			removeComments(temp, buffer);

			//marking end of input read(size of buffer must be buffersize+1)
			buffer[SIZE-1]='\0';

			offset=0;
	}
	return fp;
}


int getTokens(const char* filename, Token* tokenArray){
	int i = 0;
	int errorflag=0;//=1 if there is an error

	char buffer[SIZE] = { '\0' };

	// Position in buffer
	int offset = 0;

	int state = 1;

	Token tok;
	for(i=0; i<20; i++){
		tok.string[i] = '\0';
	}

	char lex[20] = { '\0' };
 	//stores current position in lexeme read
	int lex_i = 0;

	int tokenIndex = 0;

	int line_number = 0;

	int commentflag = 0;

	// File open
	FILE* fp;
	fp = fopen(filename, "r");

	if(fp == NULL){
		printf("File does not exist.\n");
		return -1;
	}

	fp = getStream(fp, buffer, offset);

	while(1){
		// Checks if buuffer has exhuasted of eof has occured
		if(buffer[offset] == '\0' || strlen(buffer) == 0){
			// Checks for eof
			if(feof(fp)){
				tok.name = eof;
				strcpy(tok.string, "EOF");
				tok.line_number = line_number;
				tokenArray[tokenIndex] = tok;
				tokenIndex++; //string = null for eof
				lex_i = 0;
				state = 1;
				return 1;
			} else {

				fp = getStream(fp, buffer, offset);

				offset = 0;
			}

		}

		switch(state){
			case 1:
					if(isSpace(buffer[offset])){
						state = 1;
						offset++;
					}
					else if(isNewLine(buffer[offset])){
						state = 1;
						offset++;
						line_number++;
					}
					else if(isAlphabet(buffer[offset])){
						lex[lex_i++] = buffer[offset++];
						state = 44;
					}
					else if(isDigit(buffer[offset])){
						state = 34;
						lex[lex_i++] = buffer[offset++];
					}
					else if(buffer[offset] == '+' ){
						state = 2;
						tok.name = PLUS;
						tok.line_number = line_number;
						strcpy(tok.string, "+");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] =='-'){
						state = 3;
						tok.name = MINUS;
						tok.line_number = line_number;
						strcpy(tok.string, "-");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == '*'){
						state = 5;
						tok.name = MUL;
						tok.line_number = line_number;
						strcpy(tok.string, "*");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == '/'){
						state = 10;
						tok.name = DIV;
						tok.line_number = line_number;
						strcpy(tok.string, "/");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == '<'){
						state = 11;
						lex[lex_i++] = buffer[offset++];
					}
					else if(buffer[offset] == '>'){
						state = 16;
						lex[lex_i++] = buffer[offset++];
					}
					else if(buffer[offset] == '='){
						state = 21;
						lex[lex_i++] = buffer[offset++];
					}
					else if(buffer[offset] == '!'){
						state = 23;
						lex[lex_i++] = buffer[offset++];
					}
					else if(buffer[offset] == ':'){
						state = 25;
						lex[lex_i++] = buffer[offset++];
					}
					else if(buffer[offset] == ','){
						state = 28;
						tok.name = COMMA;
						tok.line_number = line_number;
						strcpy(tok.string, ",");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == ';'){
						state = 29;
						tok.name = SEMICOL;
						tok.line_number = line_number;
						strcpy(tok.string, ";");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == '['){
						state = 30;
						tok.name = SQBO;
						tok.line_number = line_number;
						strcpy(tok.string, "[");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == ']'){
						state = 31;
						tok.name = SQBC;
						tok.line_number = line_number;
						strcpy(tok.string, "]");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == '('){
						state = 32;
						tok.name = BO;
						tok.line_number = line_number;
						strcpy(tok.string, "(");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == ')'){
						state = 33;
						tok.name = BC;
						tok.line_number = line_number;
						strcpy(tok.string, ")");
						offset++;
						tokenArray[tokenIndex] = tok;
						tokenIndex++;
						lex_i = 0;

						state = 1;
					}
					else if(buffer[offset] == '.'){
						state = 42;
						lex[lex_i++] = buffer[offset++];
					}

					else
					{
						state=52;


					}

					break;

				case 9:
					// Comment mark state
					commentflag++;
					break;

				case 11:
					//case 11 done('<'consumed and lookahead is buffer[offset] )
						if(buffer[offset] == '='){
							tok.name = LE;
							tok.line_number = line_number;
							strcpy(tok.string, "<=");
							offset++;
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
						else if(buffer[offset] == '<'){
							state = 14;
							lex[lex_i++] = buffer[offset++];
						} else {
							tok.name = LT;
							tok.line_number = line_number;
							strcpy(tok.string, "<");
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
					break;

				case 14:
					//case 14 done('<<' consumed and lookahead=buffer[offset])
						if(buffer[offset] == '<'){
							lex[lex_i++] = buffer[offset++];
							tok.name = DRIVERDEF;
							strcpy(tok.string, "<<<");
							tok.line_number = line_number;
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						} else {
							tok.name = DEF;
							tok.line_number = line_number;
							strcpy(tok.string, "<<");
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
					break;


				case 16:
						if(buffer[offset] == '='){
							tok.name = GE;
							tok.line_number = line_number;
							strcpy(tok.string, ">=");
							offset++;
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
						else if(buffer[offset] == '>'){
							state = 18;
							lex[lex_i++] = buffer[offset++];
						} else {
							tok.name = GT;
							tok.line_number = line_number;
							strcpy(tok.string, ">");
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
						break;

				case 18:
					//case 18 done('>>' consumed and lookahead=buffer[offset])
						if(buffer[offset] == '>'){
							tok.name = DRIVERENDDEF;
							tok.line_number = line_number;
							strcpy(tok.string, ">>>");
							offset++;
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						} else {
							tok.name = ENDDEF;
							tok.line_number = line_number;
							strcpy(tok.string, ">>");
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
					break;

				case 21:
				//problem:if single equal is there,no token is recognised
				//neither does it go in default case becoz of the break
						if(buffer[offset] == '='){
							tok.name = EQ;
							tok.line_number = line_number;
							strcpy(tok.string, "=");
							offset++;
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}

						else
						{
							state=53;//unknown pattern
						}
					break;

				case 23:
						if(buffer[offset] == '='){
							tok.name = NE;
							tok.line_number = line_number;
							strcpy(tok.string, "!=");
							offset++;
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
					break;

				case 25:

						if(buffer[offset] == '='){
							tok.name = ASSIGNOP;
							tok.line_number = line_number;
							strcpy(tok.string, ":=");
							offset++;
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						} else {
							tok.name = COLON;
							tok.line_number = line_number;
							strcpy(tok.string, ":");
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
					break;

				case 34:

						while(isDigit(buffer[offset])){
							state = 34;
							lex[lex_i++] = buffer[offset++];
							// Conditionally fetch buffer
							fp = getStream(fp, buffer, offset);
						}
						if(buffer[offset] == '.'){
							state = 36;
							lex[lex_i++]=buffer[offset++];
							// Conditionally fetch buffer
							fp = getStream(fp, buffer, offset);
							if(buffer[offset] == '.'){
								state = 46;//46 for 2 dots after integer
								lex[lex_i++]=buffer[offset++];
								lex_i -= 2;
								offset -= 2;
								lex[lex_i] = '\0';//for storing integer value in NUM's string
								tok.name = NUM;
								tok.line_number = line_number;
								strcpy(tok.string, lex);
								tokenArray[tokenIndex] = tok;
								tokenIndex++;
								lex_i = 0;

								state = 1;

							}
							else if(isDigit(buffer[offset])){
								state = 37;
								lex[lex_i++] = buffer[offset++];
								// Conditionally fetch buffer
								fp = getStream(fp, buffer, offset);
								while((offset < SIZE) && isDigit(buffer[offset])){
									state = 37;
									lex[lex_i++] = buffer[offset++];
									// Conditionally fetch buffer
									fp = getStream(fp, buffer, offset);
								}
								if(buffer[offset] == 'E' || buffer[offset] == 'e'){
									state = 38;
									lex[lex_i++] = buffer[offset++];
									// Conditionally fetch buffer
									fp = getStream(fp, buffer, offset);
									if(isDigit(buffer[offset])){
										state = 40;
										lex[lex_i++] = buffer[offset++];
										// Conditionally fetch buffer
										fp = getStream(fp, buffer, offset);
										while(offset<SIZE && isDigit(buffer[offset])){
											state = 40;
											lex[lex_i++] = buffer[offset++];
											// Conditionally fetch buffer
											fp = getStream(fp, buffer, offset);
										}

										lex[lex_i] = '\0';

										tok.name = RNUM;
										tok.line_number = line_number;
										strcpy(tok.string, lex);
										tokenArray[tokenIndex] = tok;
										tokenIndex++;
										lex_i = 0;

										state = 1;



									}
									else if(buffer[offset] == '+' || buffer[offset] == '-'){
										state = 39;
										lex[lex_i++] = buffer[offset++];
										// Conditionally fetch buffer
										fp = getStream(fp, buffer, offset);
										if(isDigit(buffer[offset])){
											state = 40;
											lex[lex_i++] = buffer[offset++];
											// Conditionally fetch buffer
											fp = getStream(fp, buffer, offset);
											while(offset<SIZE && isDigit(buffer[offset])){
												state = 40;
												lex[lex_i++] = buffer[offset++];
												// Conditionally fetch buffer
												fp = getStream(fp, buffer, offset);
											}

											lex[lex_i] = '\0';

											tok.name = RNUM;
											tok.line_number = line_number;
											strcpy(tok.string, lex);
											tokenArray[tokenIndex] = tok;
											tokenIndex++;
											lex_i = 0;

											state = 1;

										}

										else
										{
											state=53;//unknown pattern

										}
									}

									else
									{
										state=53;//Unknown Pattern
									}

								}
								else{
									lex[lex_i] = '\0';
									tok.name = RNUM;
									tok.line_number = line_number;
									strcpy(tok.string, lex);
									tokenArray[tokenIndex] = tok;
									tokenIndex++;
									lex_i = 0;

									state = 1;
								}
							}
							else
							{
								state=53;//eg for "1.abcd", I will have 1. as the error token
							}
						}
						else{
							lex[lex_i] = '\0';
							tok.name = NUM;
							tok.line_number = line_number;
							strcpy(tok.string, lex);
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}
						break;

				case 42:
						if(buffer[offset] == '.'){
							tok.name = RANGEOP;
							tok.line_number = line_number;
							strcpy(tok.string, "..");
							offset++;
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						} else {
							state=53;
							offset++;
							//printf("Error\n");
						}

						break;

				case 44:
					//ID or keyword
						while((isAlphabet(buffer[offset]) || buffer[offset] == '_' || isDigit(buffer[offset]))){
							state = 44;
							lex[lex_i++] = buffer[offset++];

							// Conditionally fetch buffer
							fp = getStream(fp, buffer, offset);
						}

						lex[lex_i] = '\0';

						tok = createToken(lex, line_number);

						if(tok.name == ID && (strlen(lex) > 8)){
							state = 51;//error 1
						} else{
							tokenArray[tokenIndex] = tok;
							tokenIndex++;
							lex_i = 0;
							state = 1;
						}

						break;

				case 51://error 1
					printf("ERROR_1:Identifier at line %d is longer than prescribed length\n",line_number );
					state=1;
					errorflag=1;
					break;
				case 52://error 2
					printf("ERROR_2:Unknown Symbol %c at line %d\n",buffer[offset],line_number);
					state=1;
					offset++;
					errorflag=1;
					break;

				case 53://error 3
					lex[lex_i] = '\0';
					printf("Error_3:Unknown Pattern on line %d.Lexeme so far:%s\n",line_number ,lex);
					state=1;
					errorflag=1;

					break;

				default:

					printf("Error\n");
					offset++;

		}

	}
	if(errorflag){
        return -1;
	}

    return -1;
}


int isSpace(char ch)
{
	if(ch=='\t'||ch==' '||ch=='\r')
		return 1;
	else
		return 0;
}

int isNewLine(char ch)
{
	return ch=='\n'?1:0;
}

int isAlphabet(char ch)
{
	return ((ch>=65&& ch<=90)||(ch>=97&& ch<=122))?1:0;
}

int isDigit(char ch)
{
	return ((ch>=48&& ch<=57))?1:0;

}


void removeComments(char *testcaseFile, char *cleanFile)
{
	int len=strlen(testcaseFile);
	int i=0,j=0;
	while(testcaseFile[i]!='\0')
	{
		if(testcaseFile[i]=='*' && testcaseFile[i+1]=='*')
		{
			cleanFile[j++]=' ';
			cleanFile[j++]=' ';
			i+=2;
			while(i<len-1 && !(testcaseFile[i]=='*' && testcaseFile[i+1]=='*'))
			{
				if(testcaseFile[i]=='\n')
					cleanFile[j]='\n';
				else
					cleanFile[j]=' ';
				j++;
				i++;
			}
			cleanFile[j++]=' ';
			cleanFile[j++]=' ';
			i+=2;
		}
		else
		{
			cleanFile[j]=testcaseFile[i];
			cleanFile[j+1]='\0';
			j++;
			i++;
		}
	}
}
