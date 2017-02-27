#include <stdio.h>
#include <stdlib.h>
#include "./custom_types/token.h"
#include "./custom_types/structs.h"
#include "./headers/utils.h"

void readGrammer(const char *filename, grammer g){

    FILE *f = fopen(filename, "rt");
    if (f == NULL)
        printf("File does not exist.\n");

    // Tokens are no longer
    char buffer[50];
    char ch;

    int row_num = 0;
    int word_num = 0;

    while (fscanf(f, "%s%c", buffer, &ch) == 2){

        if (word_num == 0){
            g[row_num].lhs = string_to_token(buffer);
        } else {
            g[row_num].rhs[word_num-1] = string_to_token(buffer);
        }

        // Essential for lhs and rhs
        word_num++;

        // Take care of line number
        if (ch == '\n'){
            row_num++;
            word_num = 0;
        }
    }

    fclose(f);
}

void main(){
    grammer g;

    readGrammer("./lang/grammer.txt", g);
}
