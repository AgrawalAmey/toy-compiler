#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../custom_types/token.h"
#include "../../../custom_types/structs.h"
#include "../../../headers/utils.h"
#include "../../../headers/parser.h"

void main(){
    int i, j = 0;

    grammer g;
    readGrammer("../../lang/grammer.txt", g);

    while(g[i].lhs != 0) {
        j = 0;
        printf("%s: ", token_to_string(g[i].lhs));
        while(g[i].rhs[j] != 0){
            printf("%s ", token_to_string(g[i].rhs[j]));
            j++;
        }
        i++;
        printf("\n");
    }

}
