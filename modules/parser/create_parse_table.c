#include <stdio.h>
#include <stdlib.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/parser.h"

void creatParseTable(parse_table pt){
    int i, j;
    grammer g;
    non_terminals nt;

    // This needs to be defined here because possition of these files respect to
    // caller fuction may be different
    readGrammer("../../lang/grammer.txt", g);
    readFirstAndFollow("../../lang/first.txt", "../../lang/follow.txt", nt);

    for (i = 0;  i < sizeof (g) / sizeof (g[0]);  i++){
        // If all the valid rules are over breal
        if (g[i].lhs == 0){
            break;
        }

        // Index of terminals start from 1000
        if (g[i].rhs[0] >= 1000){
            if(g[i].rhs[0] == EPISLON){

            }
            // Row indexed by non-terminals and colomn indexed by terminals
            // Index of non-terminals start from 500
            pt[g.lhs-500][g[i].rhs[0]-1000] = g[i].rhs[0];
        } else {

        }

    }
}

void main(){
    parse_table pt;
    creatParseTable(pt);
}
