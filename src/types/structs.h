// Definations of all structs
#ifndef STRUCTS
#define STRUCTS

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
typedef non_terminal non_terminals[100];

// Parse table
typedef token parse_table[100][100][20];

// Stack
typedef struct stackNode {
	token data;
	struct stackNode* next;
} stackNode;

// Tree
typedef struct parse_tree_node {
    Token data;
    int associated;
    int scopeId;
    struct parse_tree_node * children[20];
    struct parse_tree_node * parent;
    struct parse_tree_node * left;
    struct parse_tree_node * right;
} parseTreeNode;

typedef parseTreeNode ** parseTree;

// Hash table
typedef  struct{
    token type;
    int location;
    int isDefined;
    token inputTypes[20];
    token outputTypes[20];
} tableEntry;

typedef struct hashTableEntry {
    char *key;
    tableEntry data;
    struct hashTableEntry *next;
} hashTableEntry;

typedef struct {
    int size;
    hashTableEntry **table;
} hashTable;

// Symbol tabel tree (Tree of hashTables)
typedef struct symbol_table_tree_node {
    char name[20];
    hashTable * table;
    int scopeId;
    struct symbol_table_tree_node * children[20];
    struct symbol_table_tree_node * parent;
} STTNode;

typedef STTNode ** symbolTableTree;

#endif
