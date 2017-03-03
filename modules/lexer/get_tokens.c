#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/lexer.h"


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
		exit(1);
	}

}
