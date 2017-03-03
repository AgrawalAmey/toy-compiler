#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/parser.h"
#include "../../headers/utils.h"

void creatParseTable(char * grammerFile, parse_table pt){
    int i, j, k;
    grammer g;
    non_terminals nt;
    token first[30];
    int hasEpsilon = 0;

    // This needs to be defined here because possition of these files respect to
    // caller fuction may be different
    readGrammer(grammerFile, g);
    findFirstAndFollow(g, nt);

    // Zero initialization
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            for (k = 0; k < 20; k++) {
                pt[i][j][k] = 0;
            }
        }
    }

    i = j = k = 0;

    while (g[i].lhs != 0){

        // Reset first
        for (j = 0; j < 30; j++) {
            first[j] = 0;
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
            while (nt[g[i].lhs-500].follow[j] != 0) {
                // Copy rhs to appropriate place
                memcpy(pt[g[i].lhs-500][nt[g[i].lhs-500].follow[j]-1000], g[i].rhs, 20 * sizeof(token));

                j++;
            }
        }

        // Reset flags
        hasEpsilon = 0;

        i++;
    }
}
