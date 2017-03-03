#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../custom_types/token.h"
#include "../../../custom_types/structs.h"
#include "../../../headers/utils.h"
#include "../../../headers/lexer.h"


int main(int agrc, char * argv[] )
{
	// char str[40]="he****a ** \n abcdef ** pr ** there";
	// char output[40];
	// removeComments(str,output);
	// printf("%s\n",output );


	FILE* fp;
	int size=50;
	fp=fopen(argv[1],"r");

	if(fp == NULL){
		printf("File does not exist.\n");
		return -1;
	}

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
