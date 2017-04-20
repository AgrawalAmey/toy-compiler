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
} keyword_conversions[] = {
    // keywords: A subset of tokens
    { AND,        "AND"        },
    { ARRAY,      "array"      },
    { BOOLEAN,    "boolean"    },
    { BREAK,      "break"      },
    { CASE,       "case"       },
    { DECLARE,    "declare"    },
    { DEFAULT,    "default"    },
    { DRIVER,     "driver"     },
    { END,        "end"        },
    { FALSE,      "false"      },
    { FOR,        "for"        },
    { GET_VALUE,  "get_value"  },
    { IN,         "in"         },
    { INPUT,      "input"      },
    { INTEGER,    "integer"    },
    { MODULE,     "module"     },
    { OF,         "of"         },
    { OR,         "OR"         },
    { PARAMETERS, "parameters" },
    { PRINT,      "print"      },
    { PROGRAM,    "program"    },
    { REAL,       "real"       },
    { RETURNS,    "returns"    },
    { START,      "start"      },
    { SWITCH,     "switch"     },
    { TAKES,      "takes"      },
    { TRUE,       "true"       },
    { USE,        "use"        },
    { WHILE,      "while"      },
    { WITH,       "with"       }
};

// Returns token enum from string
token
string_to_keyword(char * str)
{
    int i;

    for (i = 0; i < sizeof(keyword_conversions) / sizeof(keyword_conversions[0]); i++) {
        if (!strcmp(str, keyword_conversions[i].str))
            return keyword_conversions[i].val;
    }
    return 0;
}
