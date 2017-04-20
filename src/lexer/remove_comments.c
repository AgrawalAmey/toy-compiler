#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "../utils/utils.h"
#include "./lexer.h"

void
removeComments(char * testcaseFile, char * cleanFile)
{
    int len = strlen(testcaseFile);
    int i   = 0, j = 0;

    while (testcaseFile[i] != '\0') {
        if (testcaseFile[i] == '*' && testcaseFile[i + 1] == '*') {
            cleanFile[j++] = ' ';
            cleanFile[j++] = ' ';
            i += 2;
            while (i < len - 1 && !(testcaseFile[i] == '*' && testcaseFile[i + 1] == '*')) {
                if (testcaseFile[i] == '\n')
                    cleanFile[j] = '\n';
                else
                    cleanFile[j] = ' ';
                j++;
                i++;
            }
            cleanFile[j++] = ' ';
            cleanFile[j++] = ' ';
            i += 2;
        } else {
            cleanFile[j]     = testcaseFile[i];
            cleanFile[j + 1] = '\0';
            j++;
            i++;
        }
    }
}
