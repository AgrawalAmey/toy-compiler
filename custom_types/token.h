// Enum for all tokens
// Non_terminals are indexed from 0
// Terminals are indexed from 1000

// The non_terminal for default is named default_nt to prevent name conflict

typedef enum {
    // non_terminals
	AnyTerm,
	Goal,
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
    // Terminals
    AND = 1000,
    ARRAY,
    ASSIGNOP,
    BC,
    BO,
    BOOLEAN,
    BREAK,
    CASE,
    COLON,
    COMMA,
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
    EPSILON,
	eof
} token;
