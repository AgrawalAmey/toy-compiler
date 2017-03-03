#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/lexer.h"

//IMP:Checks if we have encountered '\0' in buffer
//:if yes,we fetch from file again
//checks if '\0' is encountered,and if eof not reached,I have to fetch
FILE* getStream(FILE* fp, char * buffer, int offset){
	char temp[SIZE] = { '\0' };

	if((buffer[offset] == '\0' || strlen(buffer) == 0) && !feof(fp)){
			//for fetching new stream of size of buffer
			memset(buffer, '\0', sizeof(buffer));//end should be a '\0'

			//size should be typically 200
			//as of now assumption is that a line doesnt exceed 200 limit
			fread(temp, 1, SIZE-1, fp);

			removeComments(temp, buffer);
			
			//marking end of input read(size of buffer must be buffersize+1)
			buffer[SIZE-1]='\0';

			offset=0;
	}
	return fp;
}
