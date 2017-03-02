#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/lexer.h"

//small functions definition:End

int commentflag=0;
Token tokenArray[1000];
int tok_i;//ith token is added to the array


int count=0;//stores the number of times getStream is called
int offset,state=1,line_number,lh1=1,lh2=2;//lh1 and lh2 are lookaheads
//offset is the current character being read in the buffer
//size=size of buffer


//Token same as Token
Token* getTokens(const char* filename,Token* tokenArray)
{
	FILE* fp;
	fp=fopen(filename,"r");
	char * buffer=(char *)malloc(10000*sizeof(char));
	int i=0;
	for(i=0;i<10000;i++)
		buffer[i]='\0';
	fp=getStream(fp,buffer,10000);


	for(i=0;i<10000;i++)
	{
		tokenArray[i]=getNextToken(fp,buffer,50);
		if(tokenArray[i].name==eof)//eof encountered
		{
			break;
		}
		//printf("%s  %d\n",tokenArray[i].string,tokenArray[i].name );

	}
	return tokenArray;
}

Token getNextToken(FILE* fp,char* buffer,int size)
{
	//actual size of buffer read is size+3
	state=1;
	Token tok;
	tok.string=(char *)malloc(20*sizeof(char));
	char *lex=(char *)malloc(20*sizeof(char));


	int dummy=0;
	for(dummy=0;dummy<20;dummy++)
	{
		tok.string[dummy]='\0';
		lex[dummy]='\0';
	}//initialize bith strings with all '\0'


	int i=0;
	for(i=0;i<20;i++)
	{
		tok.string[i]='\0';
	}//initialize tok.string to \0 to maintain.
	int lex_i=0;//stores current position in lexeme read
	//char lookahead[3];

	int flag=0;//hack for last 3 symbols of the file

	while(1)
	{

		//printf("Hello\n");
		//for 2 lookaheads
		if((flag==0)&&(offset==size||buffer[offset]=='\0'||strlen(buffer)==0 ))
		{
			if(feof(fp))//end of file is reached
			{
				//printf("hello\n");
				flag=1;
				tok.name=eof;
				tok.line_number=line_number;
				return tok;//string = null for eof
			}
			else
			{
				//printf("hi\n");
				memset(buffer,'\0',sizeof(buffer));//end should be a $
				int len=strlen(buffer);

				fp=getStream(fp,buffer,size);
				offset=0;
			}

		}



	switch(state)
	{
		case 1:
				if(isSpace(buffer[offset]))
				{
					state=1;
					offset++;

				}

				else if(isNewLine(buffer[offset]))
				{
					state=1;
					offset++;
					line_number++;
				}

				else if(isAlphabet(buffer[offset]))
				{
					lex[lex_i++]=buffer[offset++];
					state=44;
				}
				else if(isDigit(buffer[offset]))
				{
					state=34;
					lex[lex_i++]=buffer[offset++];

				}

				else if(buffer[offset]=='+')
				{
					state=2;
					tok.name=PLUS;
					tok.line_number=line_number;
					tok.string="PLUS";
					offset++;
					return tok;
				}
				else if(buffer[offset]=='-')
				{
					state=3;
					tok.name=MINUS;
					tok.line_number=line_number;
					tok.string="MINUS";
					offset++;
					return tok;
				}
				else if(buffer[offset]=='*')
				{
					state=4;
					lex[lex_i++]=buffer[offset++];
				}
				else if(buffer[offset]=='/')
				{
					state=10;
					tok.name=DIV;
					tok.line_number=line_number;
					tok.string="DIV";
					offset++;
					return tok;
				}
				else if(buffer[offset]=='<')
				{
					state=11;
					lex[lex_i++]=buffer[offset++];
				}
				else if(buffer[offset]=='>')
				{
					state=16;
					lex[lex_i++]=buffer[offset++];
				}
				else if(buffer[offset]=='=')
				{
					state=21;
					lex[lex_i++]=buffer[offset++];
				}
				else if(buffer[offset]=='!')
				{
					state=23;
					lex[lex_i++]=buffer[offset++];
				}
				else if(buffer[offset]==':')
				{
					state=25;
					lex[lex_i++]=buffer[offset++];
				}
				else if(buffer[offset]==',')
				{
					state=28;
					tok.name=COMMA;
					tok.line_number=line_number;
					tok.string="COMMA";
					offset++;
					return tok;
				}
				else if(buffer[offset]==';')
				{
					state=29;
					tok.name=SEMICOL;
					tok.line_number=line_number;
					tok.string="SEMICOL";
					offset++;
					return tok;
				}
				else if(buffer[offset]=='[')
				{
					state=30;
					tok.name=SQBO;
					tok.line_number=line_number;
					tok.string="SQBO";
					offset++;
					return tok;
				}
				else if(buffer[offset]==']')
				{
					state=31;
					tok.name=SQBC;
					tok.line_number=line_number;
					tok.string="SQBC";
					offset++;
					return tok;
				}
				else if(buffer[offset]=='(')
				{
					state=32;
					tok.name=BO;
					tok.line_number=line_number;
					tok.string="BO";
					offset++;
					return tok;
				}
				else if(buffer[offset]==')')
				{
					state=33;
					tok.name=BC;
					tok.line_number=line_number;
					tok.string="BC";
					offset++;
					return tok;
				}
				else if(buffer[offset]=='.')
				{
					state=42;
					lex[lex_i++]=buffer[offset++];
				}
				else
				{
					printf("Error\n");
					//state=51;//error state
					//break;
					//while(1){}
				}

			break;





			case 4:


				if(buffer[offset]=='*')
				{
					state=6;
					tok.name=COMMENTMARK;
					tok.line_number=line_number;
					tok.string="COMMENTMARK";
					offset++;
					if(commentflag%2==1)
						state=9;
					else

						{
							//remove comments
							commentflag++;
							while(!((buffer[offset]=='*')&&(buffer[offset+1]=='*'))&&(offset < size))
							{
								if(isNewLine(buffer[offset]))
									line_number++;
								offset++;
							}


							return tok;
						}






				}
				else
				{
					state=5;
					tok.name=MUL;
					tok.line_number=line_number;
					tok.string="MUL";

					return tok;
				}
				break;//case 4 ends

			case 9:
					commentflag++;
					tok.name=COMMENTMARK;
					tok.line_number=line_number;
					tok.string="COMMENTMARK";
					return tok;
				break;//case 9 ends

			case 11:
					if(buffer[offset]=='=')
					{
						tok.name=LE;
						tok.line_number=line_number;
						tok.string="LE";
						offset++;
						return tok;
					}
					else if(buffer[offset]=='<')
					{
						state=14;
						lex[lex_i++]=buffer[offset++];
					}
					else
					{
						tok.name=LT;
						tok.line_number=line_number;
						tok.string="LT";
						return tok;
					}

				break;//case 11 done('<'consumed and lookahead is buffer[offset] )


			case 14:

					if(buffer[offset]=='<')
					{

						lex[lex_i++]=buffer[offset++];
						tok.name=DRIVERDEF;
						tok.string="DRIVERDEF";
						tok.line_number=line_number;
						return tok;
					}
					else
					{

						tok.name=DEF;
						tok.line_number=line_number;
						tok.string="DEF";
						return tok;
					}
				break;//case 14 done('<<' consumed and lookahead=buffer[offset])


			case 16:
					if(buffer[offset]=='=')
					{
						tok.name=GE;
						tok.line_number=line_number;
						tok.string="GE";
						offset++;
						return tok;
					}
					else if(buffer[offset]=='>')
					{
						state=18;
						lex[lex_i++]=buffer[offset++];
					}
					else
					{
						tok.name=GT;
						tok.line_number=line_number;
						tok.string="GT";
						return tok;
					}

			case 18:

					if(buffer[offset]=='>')
					{
						tok.name=DRIVERENDDEF;
						tok.line_number=line_number;
						tok.string="DRIVERENDDEF";
						offset++;
						return tok;
					}
					else
					{
						tok.name=ENDDEF;
						tok.line_number=line_number;
						tok.string="ENDDEF";
						return tok;
					}
				break;//case 18 done('>>' consumed and lookahead=buffer[offset])



			case 21:
					if(buffer[offset]=='=')
					{
						tok.name=EQ;
						tok.line_number=line_number;
						tok.string="EQ";
						offset++;
						return tok;
					}
				break;
				//problem:if single equal is there,no token is recognised
				//neither does it go in default case becoz of the break

			case 23:
					if(buffer[offset]=='=')
					{
						tok.name=NE;
						tok.line_number=line_number;
						tok.string="NE";
						offset++;
						return tok;
					}
				break;

			case 25:

					if(buffer[offset]=='=')
					{
						tok.name=ASSIGNOP;
						tok.line_number=line_number;
						tok.string="ASSIGNOP";
						offset++;
						return tok;
					}
					else
					{
						tok.name=COLON;
						tok.line_number=line_number;
						tok.string="COLON";
						return tok;
					}
				break;

			case 34:

					while(isDigit(buffer[offset]))
					{
						state=34;
						lex[lex_i++]=buffer[offset++];
					}
					if(buffer[offset]=='.')
					{
						state=36;
						lex[lex_i++]=buffer[offset++];
						if(buffer[offset]=='.')
						{
							state=46;//46 for 2 dots after integer
							lex[lex_i++]=buffer[offset++];
							lex_i-=2;
							offset-=2;
							tok.name=NUM;
							tok.line_number=line_number;
							tok.string=lex;
							return tok;

						}
						else if(isDigit(buffer[offset]))
						{
							state=37;
							lex[lex_i++]=buffer[offset++];
							while(isDigit(buffer[offset])&&offset<size)
							{
								state=37;
								lex[lex_i++]=buffer[offset++];
							}
							if(buffer[offset]=='E'||buffer[offset]=='e')
							{
								state=38;
								lex[lex_i++]=buffer[offset++];
								if(isDigit(buffer[offset]))
								{
									state=40;
									lex[lex_i++]=buffer[offset++];
									while(isDigit(buffer[offset])&&offset<size)
									{
										state=40;
										lex[lex_i++]=buffer[offset++];
									}
									tok.name=RNUM;
									tok.line_number=line_number;
									tok.string=lex;
									return tok;

								}
								else if(buffer[offset]=='+'||buffer[offset]=='-')
								{
									state=39;
									lex[lex_i++]=buffer[offset++];
									if(isDigit(buffer[offset]))
									{
										state=40;
										lex[lex_i++]=buffer[offset++];
										while(isDigit(buffer[offset])&&offset<size)
										{
											state=40;
											lex[lex_i++]=buffer[offset++];
										}
										tok.name=RNUM;
										tok.line_number=line_number;
										tok.string=lex;
										return tok;

									}
								}
							}
							else
							{
								tok.name=RNUM;
								tok.line_number=line_number;
								tok.string=lex;
								return tok;
							}
						}
					}
					else
					{
						tok.name=NUM;
						tok.line_number=line_number;
						tok.string=lex;
						return tok;
					}

					break;

			case 42:
					if(buffer[offset]=='.')
					{
						tok.name=RANGEOP;
						tok.line_number=line_number;
						tok.string="RANGEOP";
						offset++;
						//tok.string=lex;
						return tok;
					}
					else
					{
						printf("Error\n");
					}

					break;

			case 44://ID or keyword

					//tok.string="ID";
					while((isAlphabet(buffer[offset])||buffer[offset]=='_'||isDigit(buffer[offset])) && offset<size)
						{
							state=44;
							lex[lex_i++]=buffer[offset++];
						}


					tok=createToken(lex,line_number,tok);

					//tok.string=lex;
					if(tok.name==ID && strlen(lex)>8)
					{
						state=50;//error 1
					}
					else
						return tok;


					break;


			case 50://error 1
					printf("******ID error(length>8 found) at line %d******\n",line_number );
					state=1;
					break;
		/*	case 51://error 1
					printf("Error 51\n");
					offset++;
					state=1;
					break;
		*/

			default:
					{
						printf("Error\n");

					}





	}










	}
	//printf("%s\n",lex );

}
