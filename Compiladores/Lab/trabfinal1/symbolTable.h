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
int initSymTable(SymTable *table);
void printSymTable(SymTable *table);
int addSymTable(SymTable *table, char *identifier, Type type, char *value);
SymTableEntry *findSymTable(SymTable *table, char *identifier);
void freeSymTable(SymTable *table);

#endif