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



Token createToken(char * lex,int l,Token tok)
{
	//we shall use strcmpi for insensitive case string comparison
	tok.line_number=l;
	tok.name=ID;
	strcpy(tok.string, lex);

	int i=0;//30-number of keywords
	for(i=0;i<30;i++)
	{
		tok.name = string_to_keyword(lex);
	}
	return tok;
}


