#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./parser.h"
#include "../utils/utils.h"

void
findFirstAndFollow(grammer g, non_terminals nt)
{
    int i, j, k = 0;
    int first_indexs[100]  = { 0 };
    int follow_indexs[100] = { 0 };
    int total = 0;
    int last_index, last_total;
    token tok;

    // Initialize everything with zeros
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 20; j++) {
            nt[i].first[j]  = 0;
            nt[i].follow[j] = 0;
        }
    }

    i = j = k = 0;

    // For first
    do {
        i = 0;
        last_total = total;

        while (g[i].lhs != 0) {
            // Count before the itration
            last_index = first_indexs[g[i].lhs - 500];
            // Add new terms
            first_indexs[g[i].lhs - 500] = findFirst(g[i].lhs, g[i].rhs, nt, first_indexs[g[i].lhs - 500]);
            // Add the difference to total
            total = total + first_indexs[g[i].lhs - 500] - last_index;

            i++;
        }
    } while (total != last_total);

    // Reset variable
    total = last_total = 0;

    // Add eof
    nt[program - 500].follow[0] = eof;
    follow_indexs[program - 500]++;

    // For follow
    do {
        i = 0;
        last_total = total;
        // For all symbols
        while (g[i].lhs != 0) {
            j   = 0;
            tok = g[i].lhs;
            // For all rules
            while (g[j].lhs != 0) {
                k = 0;

                // Count before the itration
                last_index = follow_indexs[tok - 500];

                // Find the position of rhs
                while (g[j].rhs[k] != 0) {
                    if (g[j].rhs[k] == tok) {
                        // Add new terms
                        follow_indexs[tok
                          - 500] = findFollow(tok, g[j].lhs, g[j].rhs + k + 1, nt, follow_indexs[tok - 500]);
                        // Add the difference to total
                        total = total + follow_indexs[tok - 500] - last_index;

                        break;
                    }
                    k++;
                }

                j++;
            }
            i++;
        }
    } while (total != last_total);
} /* findFirstAndFollow */
