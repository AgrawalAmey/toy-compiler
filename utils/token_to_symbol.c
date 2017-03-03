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
} symbol_conversions[] = {
    // keywords: A subset of tokens
    { AND, "AND" },
	{ ARRAY, "array" },
	{ ASSIGNOP, ":=" },
	{ BC, ")" },
	{ BO, "(" },
	{ BOOLEAN, "boolean" },
	{ BREAK, "break" },
	{ CASE, "case" },
	{ COLON, ":" },
	{ COMMA, "," },
	{ DECLARE, "declare" },
	{ DEF, "def" },
	{ DEFAULT, "default" },
	{ DIV, "/" },
	{ DRIVER, "driver" },
	{ DRIVERDEF, "<<<" },
	{ DRIVERENDDEF, ">>>" },
	{ END, "end" },
	{ ENDDEF, ">>" },
	{ EQ, "==" },
	{ FALSE, "false" },
	{ FOR, "for" },
	{ GE, ">=" },
	{ GET_VALUE, "get_value" },
	{ GT, ">" },
	{ ID, "ID" },
	{ IN, "in" },
	{ INPUT, "input" },
	{ INTEGER, "integer" },
	{ LE, "<=" },
	{ LT, "<" },
	{ MINUS, "minus" },
	{ MODULE, "module" },
	{ MUL, "*" },
	{ NE, "!=" },
	{ NUM, "NUM" },
	{ OF, "of" },
	{ OR, "OR" },
	{ PARAMETERS, "parameters" },
	{ PLUS, "+" },
	{ PRINT, "print" },
    { PROGRAM, "program" },
    { RANGEOP, ".." },
    { REAL, "real" },
    { RETURNS, "returns" },
    { RNUM, "RNUM" },
    { SEMICOL, ";" },
    { SQBC, "]" },
    { SQBO, "[" },
    { START, "start" },
    { SWITCH, "switch" },
    { TAKES, "takes" },
    { TRUE, "true" },
    { USE, "use" },
    { WHILE, "while" },
    { WITH, "with" }
};

// Returns string from token enum
const char * token_to_symbol(token tok){
     int i;
     for (i = 0;  i < sizeof (symbol_conversions) / sizeof (symbol_conversions[0]);  i++){
         if (tok == symbol_conversions[i].val)
             return symbol_conversions[i].str;
     }
     printf("Invalid token: %d.\n", tok);
}
