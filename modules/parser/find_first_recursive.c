#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/parser.h"
#include "../../headers/utils.h"

// Finds first of rhs of a rule recursively
void findFirst(token *rhs, non_terminals nt, token *first, int index){
    int i = 0;
    // Flag
    int hasEpsilon = 0;
    // Index of terminals start from 1000
    // Terminal Case
    if (rhs[0] >= 1000){
        first[index] = rhs[0];

        // Check if terminal is EPSILON
        if(nt[rhs[0]].first[i] == EPSILON)
            hasEpsilon = 1;

        index++;
    } else {
        // Non-terminal case
        while (nt[rhs[0]].first[i] != 0){
            first[index] = nt[rhs[0]].first[i] ;

            // Flag is set to true if epsilon is in the first of non_terminal
            if (nt[rhs[0]].first[i] == EPSILON)
                hasEpsilon = 1;

            i++;
            index++;
        }
    }
    // Make recursive call
    if (hasEpsilon){
        findFirst(rhs+1, nt, first, index);
    }
    return;
}
