#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/lexer.h"

//buffer is assumed to already have heap allocation of memory before
//calling getStream() or getNextToken()
FILE* getStream(FILE *fp,char *buffer,int size)
{
	//size should be typically 200
	//as of now assumption is that a line doesnt exceed 200 limit


	count++;
	fread(buffer,1,size,fp);//provide buffer's size=size+3
	//as 3 extra chars read for 3 lookaheads

	//printf("%s\n",buffer );
	buffer[size-1]='\0';//marking end of input read(size of buffer must be buffersize+1)
	return fp;

}
