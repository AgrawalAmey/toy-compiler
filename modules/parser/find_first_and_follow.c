#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/parser.h"

void findFirstAndFollow(grammer g, non_terminals nt){
    int i, j, k = 0;
    int first_indexs[100], follow_indexs = { 0 };
    int total = 0;
    int last_index, last_total;
    int isLast = 0;
    token tok;

    // For first
    do{
        i = 0;
        last_total = total;

        while(g[i].lhs != 0) {
            // Count before the itration
            last_index = first_indexs[g[i].lhs-500];
            // Add new terms
            first_indexs[g[i].lhs-500] = findFirst(g[i].lhs, g[i].rhs, nt, first_indexs[g[i].lhs-500]);
            // Add the difference to total
            total = total + first_indexs[g[i].lhs-500] - last_index;

            i++;
        }

    } while(total != last_total);

    // Reset variable
    total = last_total = 0;

    // For follow
    do{
        i = 0;
        last_total = total;
        // For all symbols
        while(g[i].lhs != 0){
            j = 0;
            tok = g[i].lhs;
            // For all rules
            while(g[j].lhs != 0){
                k = 0;
                isLast = 0;
                // Count before the itration
                last_index = follow_indexs[tok-500];
                // Find the position of rhs
                while(rhs[k] != tok && rhs[k] != 0) {
                    k++;
                }
                if(rhs[k] == tok && rhs[k+1] == 0){
                    isLast = 1;
                }

                // Add new terms
                follow_indexs[tok-500] = findFirstRecursive(tok, g[i].lhs, g[i].rhs+k, nt, follow_indexs[tok-500], isLast);
                // Add the difference to total
                total = total + follow_indexs[tok-500] - last_index;
                j++;
            }
            i++;
        }

    } while(total != last_total);
}
