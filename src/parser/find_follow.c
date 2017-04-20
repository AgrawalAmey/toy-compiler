#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./parser.h"
#include "../utils/utils.h"

// Finds follow of rhs of a rule recursively
int
findFollow(token tok, token lhs, token * rhs, non_terminals nt, int index)
{
    int i = 0;
    int j = 0;

    // Flag
    int ifExists   = 0;
    int hasEpsilon = 0;

    // Possible only if tok is the right-most or everything on right can derive epsilon
    if (rhs[0] == 0) {
        while (nt[lhs - 500].follow[i] != 0) {
            j        = 0;
            ifExists = 0;

            // Check if it already exists
            while (nt[tok - 500].follow[j] != 0) {
                if (nt[tok - 500].follow[j] == nt[lhs - 500].follow[i]) {
                    ifExists = 1;
                }
                j++;
            }

            if (!ifExists && nt[lhs - 500].follow[i] != EPSILON) {
                nt[tok - 500].follow[index] = nt[lhs - 500].follow[i];
                index++;
            }

            i++;
        }
        return index;
    }

    // Index of terminals start from 1000
    // Terminal Case
    if (rhs[0] >= 1000 && rhs[0] != EPSILON) {
        j = 0;
        // Check if it already exists
        while (nt[tok - 500].follow[j] != 0) {
            if (nt[tok - 500].follow[j] == rhs[0]) {
                return index;
            }
            j++;
        }

        if (rhs[0] != EPSILON) {
            nt[tok - 500].follow[index] = rhs[0];
            index++;
        } else {
            hasEpsilon = 1;
        }
    } else {
        // Non-terminal case
        while (nt[rhs[0] - 500].first[i] != 0) {
            j        = 0;
            ifExists = 0;

            // Check if it already exists
            while (nt[tok - 500].follow[j] != 0) {
                if (nt[tok - 500].follow[j] == nt[rhs[0] - 500].first[i]) {
                    ifExists = 1;
                }
                j++;
            }

            if (!ifExists && nt[rhs[0] - 500].first[i] != EPSILON) {
                nt[tok - 500].follow[index] = nt[rhs[0] - 500].first[i];
                index++;
            }

            // Flag is set to true if epsilon is in the follow of non_terminal
            if (nt[rhs[0] - 500].first[i] == EPSILON)
                hasEpsilon = 1;

            i++;
        }
    }
    // Make recursive call
    if (hasEpsilon) {
        findFollow(tok, lhs, rhs + 1, nt, index);
    }

    return index;
} /* findFollow */
