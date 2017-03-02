#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../custom_types/token.h"
#include "../../../custom_types/structs.h"
#include "../../../headers/utils.h"
#include "../../../headers/lexer.h"

//small functions definition:End

int commentflag=0;
Token tokenArray[1000];
int tok_i;//ith token is added to the array

int num_of_errors=0;//counts number of errors in lexical analysis

int count=0;//stores the number of times getStream is called
int offset,state=1,line_number,lh1=1,lh2=2;//lh1 and lh2 are lookaheads
//offset is the current character being read in the buffer
//size=size of buffer


//end:global vars definitions

int main(int agrc, char * argv[] )
{	
	// char str[40]="he****a ** \n abcdef ** pr ** there";
	// char output[40];
	// removeComments(str,output);
	// printf("%s\n",output );


	FILE* fp;
	int size=50;
	fp=fopen(argv[1],"r");
	char * buffer=(char *)malloc((size)*sizeof(char));
	int i=0;
	for(i=0;i<size;i++)
		buffer[i]='\0';
	fp=getStream(fp,buffer,size);


	i=0;
	for(i=0;i<1000;i++)
	{
		tokenArray[i]=getNextToken(fp,buffer,size);
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

	return 0;
}