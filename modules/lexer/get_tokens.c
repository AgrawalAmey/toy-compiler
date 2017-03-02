#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/lexer.h"

extern int commentflag;
extern Token tokenArray[1000];
extern int tok_i;//ith token is added to the array

extern int num_of_errors;//counts number of errors in lexical analysis

extern int count;//stores the number of times getStream is called
extern int offset,state,line_number,lh1,lh2;//lh1 and lh2 are lookaheads
//offset is the current character being read in the buffer
//size=size of buffer

//Token same as Token
Token* getTokens(const char* filename,Token* tokenArray)
{
	FILE* fp;
	fp=fopen("filename","r");
	char * buffer=(char *)malloc(800*sizeof(char));
	int i=0;
	for(i=0;i<800;i++)
		buffer[i]='\0';
	fp=getStream(fp,buffer,800);
	i=0;
	for(i=0;i<1000;i++)
	{
		tokenArray[i]=getNextToken(fp,buffer,800);
		if(tokenArray[i].name==COMMENTMARK)
			{
				i--;
				continue;
			}
		if(tokenArray[i].name==eof)//eof encountered
		{
			printf("%s  %d  %d\n",tokenArray[i].string,tokenArray[i].name,state );
			break;
		}
		printf("%s  %d  %d\n",tokenArray[i].string,tokenArray[i].name,state );

	}
} //createTokens ends here


Token getNextToken(FILE* fp,char* buffer,int size)
{
	//actual size of buffer read is size+3
	state=1;
	Token tok;
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
	
	int flag=0;//flag=1 when eof is reached

	while(1)
	{

		//printf("Hello\n");
		//for 2 lookaheads
		if(flag==0 && (buffer[offset]=='\0'||strlen(buffer)==0 ))
		{
			//printf("offset:%d\n",offset );
			if(feof(fp))//end of file is reached
			{
				//printf("hello\n");
				flag=1;
				tok.name=eof;
				strcpy(tok.string, "EOF");
				tok.line_number=line_number;
				return tok;//string = null for eof
			}
			else
			{
				//printf("hi\n");
				int len=strlen(buffer);
				//printf("\n\n%s\n\n", buffer);
				

				//for fetching new stream of size of buffer
				memset(buffer,'\0',sizeof(buffer));//end should be a '\0'
							
				fp=getStream(fp,buffer,size);
				//printf("\n%s\n", buffer);
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
					strcpy(tok.string, "PLUS");
					offset++;
					return tok;
				}
				else if(buffer[offset]=='-')
				{
					state=3;
					tok.name=MINUS;
					tok.line_number=line_number;
					strcpy(tok.string, "MINUS");
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
					strcpy(tok.string, "DIV");
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
					strcpy(tok.string, "COMMA");
					offset++;
					return tok;
				}
				else if(buffer[offset]==';')
				{
					state=29;
					tok.name=SEMICOL;
					tok.line_number=line_number;
					strcpy(tok.string, "SEMICOL");
					offset++;
					return tok;
				}
				else if(buffer[offset]=='[')
				{
					state=30;
					tok.name=SQBO;
					tok.line_number=line_number;
					strcpy(tok.string, "SQBO");
					offset++;
					return tok;
				}
				else if(buffer[offset]==']')
				{
					state=31;
					tok.name=SQBC;
					tok.line_number=line_number;
					strcpy(tok.string, "SQBC");
					offset++;
					return tok;
				}
				else if(buffer[offset]=='(')
				{
					state=32;
					tok.name=BO;
					tok.line_number=line_number;
					strcpy(tok.string, "BO");
					offset++;
					return tok;
				}
				else if(buffer[offset]==')')
				{
					state=33;
					tok.name=BC;
					tok.line_number=line_number;
					strcpy(tok.string, "BC");
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
					printf("ERROR_2:Unknown Symbol %c at line %d\n",buffer[offset],line_number);
					offset++;
					num_of_errors++;
					//printf("1\n");
					//while(1){}
					//state=51;//error state
					//break;
					//while(1){}
				}
				
			break;





			case 4:


				if(buffer[offset]=='*')
				{
					state=6;
					lex[lex_i++]=buffer[offset++];
					fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
					//if yes:fetch new else dont do anything
					tok.name=COMMENTMARK;
					tok.line_number=line_number;
					strcpy(tok.string, "COMMENTMARK");
					offset++;
					if(commentflag%2==1)
						state=9;
					else

						{
							//remove comments
							commentflag++;
							while(!((buffer[offset]=='*')&&(buffer[offset+1]=='*'))&&(offset < size-1))
							{
								if(isNewLine(buffer[offset]))
									line_number++;
								offset++;
								fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
								//if yes:fetch new else dont do anything
							}
							

							return tok;
						}

					

					


				}
				else
				{
					state=5;
					tok.name=MUL;
					tok.line_number=line_number;
					strcpy(tok.string, "MUL");
					
					return tok;
				}
				break;//case 4 ends

			case 9:
					commentflag++;
					//printf("*******Case 9 ********\n");
					tok.name=COMMENTMARK;
					tok.line_number=line_number;
					strcpy(tok.string, "COMMENTMARK");
					return tok;
				break;//case 9 ends

			case 11:
					if(buffer[offset]=='=')
					{
						tok.name=LE;
						tok.line_number=line_number;
						strcpy(tok.string, "LE");
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
						strcpy(tok.string, "LT");
						return tok;
					}

				break;//case 11 done('<'consumed and lookahead is buffer[offset] )


			case 14:

					if(buffer[offset]=='<')
					{
						
						lex[lex_i++]=buffer[offset++];
						tok.name=DRIVERDEF;
						strcpy(tok.string, "DRIVERDEF");
						tok.line_number=line_number;
						return tok;
					}
					else
					{

						tok.name=DEF;
						tok.line_number=line_number;
						strcpy(tok.string, "DEF");
						return tok;
					}
				break;//case 14 done('<<' consumed and lookahead=buffer[offset])


			case 16:
					if(buffer[offset]=='=')
					{
						tok.name=GE;
						tok.line_number=line_number;
						strcpy(tok.string, "GE");
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
						strcpy(tok.string, "GT");
						return tok;
					}

			case 18:

					if(buffer[offset]=='>')
					{
						tok.name=DRIVERENDDEF;
						tok.line_number=line_number;
						strcpy(tok.string, "DRIVERENDDEF");
						offset++;
						return tok;
					}
					else
					{
						tok.name=ENDDEF;
						tok.line_number=line_number;
						strcpy(tok.string, "ENDDEF");
						return tok;
					}
				break;//case 18 done('>>' consumed and lookahead=buffer[offset])



			case 21:
					if(buffer[offset]=='=')
					{
						tok.name=EQ;
						tok.line_number=line_number;
						strcpy(tok.string, "EQ");
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
						strcpy(tok.string, "NE");
						offset++;
						return tok;
					}
				break;

			case 25:

					if(buffer[offset]=='=')
					{
						tok.name=ASSIGNOP;
						tok.line_number=line_number;
						strcpy(tok.string, "ASSIGNOP");
						offset++;
						return tok;
					}
					else
					{
						tok.name=COLON;
						tok.line_number=line_number;
						strcpy(tok.string, "COLON");
						return tok;
					}
				break;

			case 34:

					while(isDigit(buffer[offset]))
					{
						state=34;
						lex[lex_i++]=buffer[offset++];	
						fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything					
					}
					if(buffer[offset]=='.')
					{
						state=36;
						lex[lex_i++]=buffer[offset++];
						fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything
						if(buffer[offset]=='.')
						{
							state=46;//46 for 2 dots after integer
							lex[lex_i++]=buffer[offset++];
							//fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything
							lex_i-=2;
							offset-=2;
							lex[lex_i]='\0';//for storing integer value in NUM's string
							tok.name=NUM;
							tok.line_number=line_number;
							strcpy(tok.string, lex);
							return tok;

						}
						else if(isDigit(buffer[offset]))
						{
							state=37;
							lex[lex_i++]=buffer[offset++];
							fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything
							while(isDigit(buffer[offset])&&offset<size)
							{
								state=37;
								lex[lex_i++]=buffer[offset++];
								fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything						
							}
							if(buffer[offset]=='E'||buffer[offset]=='e')
							{
								state=38;
								lex[lex_i++]=buffer[offset++];
								fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything
								if(isDigit(buffer[offset]))
								{
									state=40;
									lex[lex_i++]=buffer[offset++];
									fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything
									while(isDigit(buffer[offset])&&offset<size)
									{
										state=40;
										lex[lex_i++]=buffer[offset++];
										fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything						
									}
									tok.name=RNUM;
									tok.line_number=line_number;
									strcpy(tok.string, lex);
									return tok;

								}
								else if(buffer[offset]=='+'||buffer[offset]=='-')
								{
									state=39;
									lex[lex_i++]=buffer[offset++];
									fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything
									if(isDigit(buffer[offset]))
									{
										state=40;
										lex[lex_i++]=buffer[offset++];
										fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything
										while(isDigit(buffer[offset])&&offset<size)
										{
											state=40;
											lex[lex_i++]=buffer[offset++];	
											fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything					
										}
										tok.name=RNUM;
										tok.line_number=line_number;
										strcpy(tok.string, lex);
										return tok;

									}
								}
							}
							else
							{
								tok.name=RNUM;
								tok.line_number=line_number;
								strcpy(tok.string, lex);
								return tok;
							}
						}
					}
					else
					{
						tok.name=NUM;
						tok.line_number=line_number;
						strcpy(tok.string, lex);
						return tok;
					}

					break;

			case 42:
					if(buffer[offset]=='.')
					{
						tok.name=RANGEOP;
						tok.line_number=line_number;
						strcpy(tok.string, "RANGEOP");
						offset++;
						return tok;
					}
					else
					{
						printf("Error\n");
						printf("2\n");
						while(1){}
					}

					break;

			case 44://ID or keyword

					//tok.string, "ID"
					//printf("ID started\n");
					while((isAlphabet(buffer[offset])||buffer[offset]=='_'||isDigit(buffer[offset])))
						{
							
							state=44;
							lex[lex_i++]=buffer[offset++];	

							fetch_or_not(fp,buffer,flag,size);//checks if we have reached end of buffer
						//if yes:fetch new else dont do anything


											
						}
						









					tok=createToken(lex,line_number,tok);
					
					if(tok.name==ID && strlen(lex)>8)
					{
						state=50;//error 1
					}
					else
						return tok;


					break;


			case 50://error 1
					printf("Identifier at line %d is longer than prescribed length\n",line_number );
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
						printf("3\n");
						while(1){}
						
					}





	}


	







	}
	//printf("%s\n",lex );

}
