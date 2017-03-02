#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/parser.h"
#include "../../headers/utils.h"

// Finds follow of rhs of a rule recursively
int findFollow(token tok, token lhs, token *rhs, non_terminals nt, int index, int hasEpsilonLast){
    int i = 0;
    // Flag
    int hasEpsilon = 0;

    if (rhs[0] == 0){
        // If the rhs can derive epsilon
        if(hasEpsilonLast){
            while (nt[lhs-500].follow[i] != 0){
                nt[tok-500].follow[index] = nt[lhs-500].follow[i] ;
                i++;
                index++;
            }
        }
        return index;
    }
    // Index of terminals start from 1000
    // Terminal Case
    if (rhs[0] >= 1000 && rhs[0] != EPSILON){
        nt[tok-500].follow[index] = rhs[i+1];

        index++;
    } else {
        // Non-terminal case
        while (nt[rhs[0]-500].first[i] != 0){
            nt[tok-500].follow[index] = nt[rhs[0]-500].first[i] ;

            // Flag is set to true if epsilon is in the follow of non_terminal
            if (nt[rhs[0]-500].first[i] == EPSILON)
                hasEpsilon = 1;

            i++;
            index++;
        }
    }
    // Make recursive call
    if (hasEpsilon){
        findFollow(tok, lhs, rhs+1, nt, index, hasEpsilon);
    }
    return index;
}
