#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./code_gen.h"
#include "../utils/utils.h"

void
genrateCodeForExpressions(parseTreeNode ** t)
{
    int i;

    if (*t == NULL) {
        return;
    }

    // Bottom-up but right to left travelsal
    for (i = 0; i < 20; i++) {
        genrateCodeForExpressions(t->children[i]);
    }
}
