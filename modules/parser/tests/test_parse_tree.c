#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../custom_types/token.h"
#include "../../../custom_types/structs.h"
#include "../../../headers/utils.h"
#include "../../../headers/parser.h"

void main(){
    parse_table pt;
    tree t;
    t = createTree();

    Token * input;

    creatParseTable("../../lang/grammer.txt", "../../lang/first.txt", "../../lang/follow.txt", pt);

    creatParseTree(pt, t, input);

    printInorder(t);
}
