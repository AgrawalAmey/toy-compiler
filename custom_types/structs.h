// Definations of all structs

// For token coined by laxer
typedef struct{
    token name;
    char string[20];
    int line_number;
} Token;

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
