#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/lexer.h"

//small functions definition:End

extern int commentflag;
extern Token tokenArray[1000];
extern int tok_i;//ith token is added to the array

extern int num_of_errors;//counts number of errors in lexical analysis

extern int count;//stores the number of times getStream is called
extern int offset,state,line_number,lh1,lh2;//lh1 and lh2 are lookaheads
//offset is the current character being read in the buffer
//size=size of buffer


//end:global vars definitions


//small functions definition:Start

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