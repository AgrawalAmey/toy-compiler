#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../custom_types/token.h"
#include "../../../custom_types/structs.h"
#include "../../../headers/utils.h"
#include "../../../headers/parser.h"

void main(){
    int i, j = 0;

    non_terminals nt;
    readFirstAndFollow("../../lang/first.txt", "../../lang/follow.txt", nt);

    for(i=0; i<100; i++) {
        j = 0;
        printf("%s: ", token_to_string(i+500));
        while(nt[i].first[j] != 0){
            printf("%s ", token_to_string(nt[i].first[j]));
            j++;
        }
        printf("\n");
        j = 0;
        printf("%s: ", token_to_string(i+500));
        while(nt[i].follow[j] != 0){
            printf("%s ", token_to_string(nt[i].follow[j]));
            j++;
        }
        printf("\n");
    }
}
