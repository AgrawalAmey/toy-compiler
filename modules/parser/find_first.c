#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/parser.h"
#include "../../headers/utils.h"

// Finds first of rhs of a rule recursively
int findFirst(token tok, token *rhs, non_terminals nt, int index){

    int i = 0;
    int j = 0;
    // Flag
    int hasEpsilon = 0;
    int ifExists = 0;

    if (rhs[0] == 0){
        while(nt[tok-500].first[j] != 0){
            if (nt[tok-500].first[j] == EPSILON) {
                return index;
            }
            j++;
        }
        return index;
    }

    // Index of terminals start from 1000
    // Terminal Case
    if (rhs[0] >= 1000){
        j = 0;
        // Check if it already exists
        while(nt[tok-500].first[j] != 0){
            if (nt[tok-500].first[j] == rhs[0]) {
                return index;
            }
            j++;
        }

        nt[tok-500].first[index] = rhs[0];

        // Check if terminal is EPSILON
        if(rhs[0] == EPSILON)
            hasEpsilon = 1;

        index++;
    } else {
        // Non-terminal case
        while (nt[rhs[0]-500].first[i] != 0){

            ifExists = 0;
            j = 0;

            // Check if it already exists
            while(nt[tok-500].first[j] != 0){
                if (nt[tok-500].first[j] == nt[rhs[0]-500].first[i]) {
                    ifExists = 1;
                }
                j++;
            }

            if(!ifExists && nt[rhs[0]-500].first[i] != EPSILON){
                nt[tok-500].first[index] = nt[rhs[0]-500].first[i];
                index++;
            }

            // Flag is set to true if epsilon is in the first of non_terminal
            if (nt[rhs[0]-500].first[i] == EPSILON)
                hasEpsilon = 1;

            i++;
        }
    }
    // Make recursive call
    if (hasEpsilon){
        findFirst(tok, rhs+1, nt, index);
    }
    return index;
}
