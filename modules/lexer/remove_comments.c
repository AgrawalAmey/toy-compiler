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

void removeComments(char *testcaseFile,char *cleanFile)
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
