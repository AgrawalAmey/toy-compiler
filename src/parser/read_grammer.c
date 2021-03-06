#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./parser.h"
#include "../utils/utils.h"

int
readGrammer(char * filename, grammer g)
{
    int i, j;
    FILE * f = fopen(filename, "rt");

    if (f == NULL) {
        printf("Grammer File does not exist.\n");
        return -1;
    }
    // Tokens are no longer
    char buffer[50];
    char ch;

    int row_num  = 0;
    int word_num = 0;

    // Initialize everything with zeros
    for (i = 0; i < 100; i++) {
        g[i].lhs = 0;
        for (j = 0; j < 20; j++) {
            g[i].rhs[j] = 0;
        }
    }

    while (fscanf(f, "%s%c", buffer, &ch) == 2) {
        if (word_num == 0) {
            g[row_num].lhs = string_to_token(buffer);
        } else {
            g[row_num].rhs[word_num - 1] = string_to_token(buffer);
        }

        // Essential for lhs and rhs
        word_num++;

        // Take care of line number
        if (ch == '\n') {
            row_num++;
            word_num = 0;
        }
    }

    fclose(f);
} /* readGrammer */
