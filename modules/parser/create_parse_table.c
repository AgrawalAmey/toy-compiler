#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/parser.h"

void creatParseTable(char * grammerFile, char * firstFile, char * followFile, parse_table pt){
    int i, j;
    grammer g;
    non_terminals nt;
    token first[30];
    int hasEpsilon = 0;
    int hasEOF = 0;

    // This needs to be defined here because possition of these files respect to
    // caller fuction may be different
    readGrammer(grammerFile, g);
    readFirstAndFollow(firstFile, followFile, nt);

    for (i = 0;  i < sizeof (g) / sizeof (g[0]);  i++){

        // If all the valid rules are over breal
        if (g[i].lhs == 0){
            break;
        }

        // Get the first set for rhs
        findFirstRecursive(g[i].rhs, nt, first, 0);

        // The three cases

        // Iterate over first set
        j = 0;
        while (first[j] != 0) {
            // Copy rhs to appropriate place
            memcpy(pt[g[i].lhs-500][first[j]-1000], g[i].rhs, 20 * sizeof(token));

            // Check if terminal is EPSILON
            if(first[j] == EPSILON)
                hasEpsilon = 1;

            j++;
        }

        // If epsilon is in first of rhs consider follow of A
        if (hasEpsilon){
            j = 0;
            while (nt[g[i].lhs].follow[j] != 0) {
                // Copy rhs to appropriate place
                memcpy(pt[g[i].lhs-500][nt[g[i].lhs].follow[j]-1000], g[i].rhs, 20 * sizeof(token));

                // Check if terminal is EOF
                if(first[j] == eof)
                    hasEOF = 1;

                j++;
            }
        }

        if (hasEOF) {
            memcpy(pt[g[i].lhs-500][eof-1000], g[i].rhs, 20 * sizeof(token));
        }

        // Reset flags
        hasEpsilon = 0;
        hasEOF = 0;
    }
}
