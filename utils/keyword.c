#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../custom_types/token.h"
#include "../custom_types/structs.h"
#include "../headers/utils.h"

// Kind of look-up table to convert string to corrosponding enum
const static struct {
    token val;
    const char *str;
} keyword_conversions[] = {
    // keywords: A subset of tokens
    { AND, "AND" },
    { ARRAY, "ARRAY" },
    { BOOLEAN, "BOOLEAN" },
    { BREAK, "BREAK" },
    { CASE, "CASE" },
    { DECLARE, "DECLARE" },
    { DEFAULT, "DEFAULT" },
    { DRIVER, "DRIVER" },
    { END, "END" },
    { FALSE, "FALSE" },
    { FOR, "FOR" },
    { GET_VALUE, "GET_VALUE" },
    { IN, "IN" },
    { INPUT, "INPUT" },
    { INTEGER, "INTEGER" },
    { MODULE, "MODULE" },
    { OF, "OF" },
    { OR, "OR" },
    { PARAMETERS, "PARAMETERS" },
    { PRINT, "PRINT" },
    { PROGRAM, "PROGRAM" },
    { REAL, "REAL" },
    { RETURNS, "RETURNS" },
    { START, "START" },
    { SWITCH, "SWITCH" },
    { TAKES, "TAKES" },
    { TRUE, "TRUE" },
    { USE, "USE" },
    { WHILE, "WHILE" },
    { WITH, "WITH" }
};

// Returns token enum from string
token string_to_keyword(const char *str){
     int i;
     for (i = 0;  i < sizeof (keyword_conversions) / sizeof (keyword_conversions[0]);  i++){
         if (!strcmp (str, keyword_conversions[i].str))
             return keyword_conversions[i].val;
     }
     printf("Invalid keyword string: %s.\n", str);
}

// Returns string from keyword enum
const char * keyword_to_string(token tok){
     int i;
     for (i = 0;  i < sizeof (keyword_conversions) / sizeof (keyword_conversions[0]);  i++){
         if (tok == keyword_conversions[i].val)
             return keyword_conversions[i].str;
     }
     printf("Invalid keyword: %d.\n", tok);
}
