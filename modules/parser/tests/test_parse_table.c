#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../custom_types/token.h"
#include "../../../custom_types/structs.h"
#include "../../../headers/utils.h"
#include "../../../headers/parser.h"

void main(){
    int i, j, k = 0;

    parse_table pt;

    creatParseTable("../../../lang/grammer.txt", pt);

    for(i=0; i<51; i++) {
        for (j = 0; j < 58; j++) {
            k = 0;
            printf("%s and %s:\n", token_to_string(i+500), token_to_string(j+1000));
            while (pt[i][j][k] != 0) {
                printf("%s ", token_to_string(pt[i][j][k]));
                k++;
            }
            printf("\n");
        }
    }
}
