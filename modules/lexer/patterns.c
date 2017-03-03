#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/lexer.h"

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
