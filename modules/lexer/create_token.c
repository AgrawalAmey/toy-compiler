#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/lexer.h"


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
