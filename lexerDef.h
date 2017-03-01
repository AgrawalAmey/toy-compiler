// Definations of all structs



typedef enum {
    // non_terminals
	AnyTerm=0,
	Goal=1,
	N1,
	N2,
	N3,
	N4,
	N5,
	N7,
	N8,
	N9,
	arithmeticExpr,
	arithmeticOrBooleanExpr,
	assignmentStmt,
	caseStmts,
	condionalStmt,
	dataType,
	declareStmt,
	default_nt,
	driverModule,
	expression,
	factor,
	idList,
	INDEX,
	input_plist,
	ioStmt,
	iterativeStmt,
	logicalOp,
	lvalueARRStmt,
	lvalueIDStmt,
	module,
	moduleDeclaration,
	moduleDeclarations,
	moduleDef,
	moduleReuseStmt,
	op1,
	op2,
	optional,
	otherModules,
	output_plist,
	program,
	range,
	relationalOp,
	ret,
	simpleStmt,
	statement,
	statements,
	term,
	type,
	value,
	var,
	whichId,
	whichStmt,
    

	//left blank only to match up line numbers




































	//left blank only to match up line numbers

    // Terminals
    AND =1000,
    ARRAY,
    ASSIGNOP,
    BC,
    BO,
    BOOLEAN,
    BREAK,
    CASE,
    COLON,
    COMMA,
    COMMENTMARK,
    DECLARE,
    DEF,
    DEFAULT,
    DIV,
    DRIVER,
    DRIVERDEF,
    DRIVERENDDEF,
    END,
    ENDDEF,
    EQ,
    FALSE,
    FOR,
    GE,
    GET_VALUE,
    GT,
    ID,
    IN,
    INPUT,
    INTEGER,
    LE,
    LT,
    MINUS,
    MODULE,
    MUL,
    NE,
    NUM,
    OF,
    OR,
    PARAMETERS,
    PLUS,
    PRINT,
    PROGRAM,
    RANGEOP,
    REAL,
    RETURNS,
    RNUM,
    SEMICOL,
    SQBC,
    SQBO,
    START,
    SWITCH,
    TAKES,
    TRUE,
    USE,
    WHILE,
    WITH,
    $,
    EPSILON,
	eof
} token;



const static struct {
    token val;
    const char *str;
} convert[] = {
//the keywords:total 30 keywords
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
    { WITH, "WITH" },



};


// For token coined by laxer
typedef struct{
    token name;
    char *string;
    int line_number;
} Token;
typedef Token tokenInfo;
// For storing rules
typedef struct{
    token lhs;
    token rhs[20];
} rule;

// Grammer (Just because I can)
typedef rule grammer[100];

// Used for each non-terminal.
// Stores first and follow of each non terminal
typedef struct{
    token first[20];
    token follow[20];
} non_terminal;

// A bit of hack: the array of non_terminals will be indexed by enum Token
typedef non_terminal non_terminals[50]; 

// Parse table
typedef token parse_table[100][100];