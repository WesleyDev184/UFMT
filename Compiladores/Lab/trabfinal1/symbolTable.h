/*
 *
 * UFMT - Universidade Federal de Mato Grosso
 * Laboratório de Compiladores
 * Author: Wesley Antonio Junior dos Santos
 * RGA:202011722024
 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SIZE_HASH_ARRAY 20
#define MAX_SIZE_SYMBOL 32

typedef enum
{
	INTEGER,
	REAL,
	STRING
} Type;

extern int cont_lines;

// Data type declaration
struct symTableEntry
{
	char identifier[MAX_SIZE_SYMBOL];
	Type type;
	char *value;
	int len_value;
};
typedef struct symTableEntry SymTableEntry;

// Data type for node definition
struct symTableNode
{
	SymTableEntry data;
	struct symTableNode *next;
};
typedef struct symTableNode SymTableNode;

struct symTable
{
	SymTableNode *array;
	int max_size;
	int size;
};
typedef struct symTable SymTable;

extern SymTable table;

// Function prototypes

/**
 * @brief Initialize the symbol table
 * @param table Pointer to the symbol table structure
 * @return 1 on success, 0 on failure
 */
int initSymTable(SymTable *table);

/**
 * @brief Print the contents of the symbol table
 * @param table Pointer to the symbol table structure
 */
void printSymTable(SymTable *table);

/**
 * @brief Add a new symbol to the table
 * @param table Pointer to the symbol table structure
 * @param identifier Variable name
 * @param type Variable type (INTEGER, REAL, STRING)
 * @param value Initial value (can be NULL)
 * @return 1 on success, 0 on failure
 */
int addSymTable(SymTable *table, char *identifier, Type type, char *value);

/**
 * @brief Find a symbol in the table
 * @param table Pointer to the symbol table structure
 * @param identifier Variable name to search for
 * @return Pointer to symbol entry if found, NULL otherwise
 */
SymTableEntry *findSymTable(SymTable *table, char *identifier);

/**
 * @brief Free all memory allocated by the symbol table
 * @param table Pointer to the symbol table structure
 */
void freeSymTable(SymTable *table);

#endif