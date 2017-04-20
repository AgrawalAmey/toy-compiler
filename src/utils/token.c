#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "./utils.h"

// Kind of look-up table to convert string to corrosponding enum
static struct {
    token        val;
    char * str;
} conversions[] = {
    { AnyTerm,                 "AnyTerm"                 },
    { N1,                      "N1"                      },
    { N2,                      "N2"                      },
    { N3,                      "N3"                      },
    { N4,                      "N4"                      },
    { N5,                      "N5"                      },
    { N7,                      "N7"                      },
    { N8,                      "N8"                      },
    { N9,                      "N9"                      },
    { arithmeticExpr,          "arithmeticExpr"          },
    { arithmeticOrBooleanExpr, "arithmeticOrBooleanExpr" },
    { assignmentStmt,          "assignmentStmt"          },
    { caseStmts,               "caseStmts"               },
    { conditionalStmt,         "conditionalStmt"         },
    { dataType,                "dataType"                },
    { declareStmt,             "declareStmt"             },
    { default_nt,              "default"                 },
    { driverModule,            "driverModule"            },
    { expression,              "expression"              },
    { factor,                  "factor"                  },
    { idList,                  "idList"                  },
    { INDEX,                   "index"                   },
    { input_plist,             "input_plist"             },
    { ioStmt,                  "ioStmt"                  },
    { iterativeStmt,           "iterativeStmt"           },
    { logicalOp,               "logicalOp"               },
    { lvalueARRStmt,           "lvalueARRStmt"           },
    { lvalueIDStmt,            "lvalueIDStmt"            },
    { module,                  "module"                  },
    { moduleDeclaration,       "moduleDeclaration"       },
    { moduleDeclarations,      "moduleDeclarations"      },
    { moduleDef,               "moduleDef"               },
    { moduleReuseStmt,         "moduleReuseStmt"         },
    { op1,                     "op1"                     },
    { op2,                     "op2"                     },
    { optional,                "optional"                },
    { otherModules,            "otherModules"            },
    { output_plist,            "output_plist"            },
    { program,                 "program"                 },
    { range,                   "range"                   },
    { relationalOp,            "relationalOp"            },
    { ret,                     "ret"                     },
    { simpleStmt,              "simpleStmt"              },
    { statement,               "statement"               },
    { statements,              "statements"              },
    { term,                    "term"                    },
    { type,                    "type"                    },
    { value,                   "value"                   },
    { var,                     "var"                     },
    { whichId,                 "whichId"                 },
    { whichStmt,               "whichStmt"               },
    { AND,                     "AND"                     },
    { ARRAY,                   "ARRAY"                   },
    { ASSIGNOP,                "ASSIGNOP"                },
    { BC,                      "BC"                      },
    { BO,                      "BO"                      },
    { BOOLEAN,                 "BOOLEAN"                 },
    { BREAK,                   "BREAK"                   },
    { CASE,                    "CASE"                    },
    { COLON,                   "COLON"                   },
    { COMMA,                   "COMMA"                   },
    { DECLARE,                 "DECLARE"                 },
    { DEF,                     "DEF"                     },
    { DEFAULT,                 "DEFAULT"                 },
    { DIV,                     "DIV"                     },
    { DRIVER,                  "DRIVER"                  },
    { DRIVERDEF,               "DRIVERDEF"               },
    { DRIVERENDDEF,            "DRIVERENDDEF"            },
    { END,                     "END"                     },
    { ENDDEF,                  "ENDDEF"                  },
    { EQ,                      "EQ"                      },
    { FALSE,                   "FALSE"                   },
    { FOR,                     "FOR"                     },
    { GE,                      "GE"                      },
    { GET_VALUE,               "GET_VALUE"               },
    { GT,                      "GT"                      },
    { ID,                      "ID"                      },
    { IN,                      "IN"                      },
    { INPUT,                   "INPUT"                   },
    { INTEGER,                 "INTEGER"                 },
    { LE,                      "LE"                      },
    { LT,                      "LT"                      },
    { MINUS,                   "MINUS"                   },
    { MODULE,                  "MODULE"                  },
    { MUL,                     "MUL"                     },
    { NE,                      "NE"                      },
    { NUM,                     "NUM"                     },
    { OF,                      "OF"                      },
    { OR,                      "OR"                      },
    { PARAMETERS,              "PARAMETERS"              },
    { PLUS,                    "PLUS"                    },
    { PRINT,                   "PRINT"                   },
    { PROGRAM,                 "PROGRAM"                 },
    { RANGEOP,                 "RANGEOP"                 },
    { REAL,                    "REAL"                    },
    { RETURNS,                 "RETURNS"                 },
    { RNUM,                    "RNUM"                    },
    { SEMICOL,                 "SEMICOL"                 },
    { SQBC,                    "SQBC"                    },
    { SQBO,                    "SQBO"                    },
    { START,                   "START"                   },
    { SWITCH,                  "SWITCH"                  },
    { TAKES,                   "TAKES"                   },
    { TRUE,                    "TRUE"                    },
    { USE,                     "USE"                     },
    { WHILE,                   "WHILE"                   },
    { WITH,                    "WITH"                    },
    { COMMENTMARK,             "COMMENTMARK"             },
    { EPSILON,                 "EPSILON"                 },
    { eof,                     "EOF"                     }
};

// Returns token enum from string
token
string_to_token(char * str)
{
    int i;

    for (i = 0; i < sizeof(conversions) / sizeof(conversions[0]); i++) {
        if (!strcmp(str, conversions[i].str))
            return conversions[i].val;
    }
    printf("Invalid token string: %s.\n", str);
}

// Returns string from token enum
char *
token_to_string(token tok)
{
    int i;

    for (i = 0; i < sizeof(conversions) / sizeof(conversions[0]); i++) {
        if (tok == conversions[i].val)
            return conversions[i].str;
    }
    printf("Invalid token: %d.\n", tok);
}
