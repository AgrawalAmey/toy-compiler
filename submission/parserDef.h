// Batch Number: 55
// Amey Agrawal: 2014A7PS148P
// Jaikumar Balani 2014A7PS022P

// Definations for all parser data defs
#ifndef PARSERDEF
#define PARSERDEF

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
typedef non_terminal non_terminals[100];

// Parse table
typedef token parse_table[100][100][20];

// Stack
typedef struct stackNode {
	token data;
	struct stackNode* next;
} stackNode;

// Tree
typedef struct tree_node {
    Token data;
    int associated;
    struct tree_node * children[20];
    struct tree_node * parent;
} treeNode;

typedef treeNode ** tree;


#endif // PARSERDEF
