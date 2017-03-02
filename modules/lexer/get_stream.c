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


//buffer is assumed to already have heap allocation of memory before 
//calling getStream() or getNextToken()
FILE* getStream(FILE *fp,char *buffer,int size)
{
	//size should be typically 200
	//as of now assumption is that a line doesnt exceed 200 limit


	count++;
	fread(buffer,1,size-1,fp);

	//printf("%s\n",buffer );
	buffer[size-1]='\0';//marking end of input read(size of buffer must be buffersize+1)
	return fp;

}


//IMP:Checks if we have encountered '\0' in buffer
//:if yes,we fetch from file again
//checks if '\0' is encountered,and if eof not reached,I have to fetch
char * fetch_or_not(FILE* fp,char * buffer,int flag,int size)
{	
	if(flag==0 && (buffer[offset]=='\0'||strlen(buffer)==0 ) && !feof(fp))
		{
			//for fetching new stream of size of buffer
			memset(buffer,'\0',sizeof(buffer));//end should be a '\0'
						
			fp=getStream(fp,buffer,size);
			//printf("\n\n%s\n\n", buffer);
			offset=0;
		}

	return buffer;

}

