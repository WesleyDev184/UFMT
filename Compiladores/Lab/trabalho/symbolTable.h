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
	FLOAT,
	STRING,
	CHAR,
	BOOL
} Type;

// Parameter structure for function parameters
typedef struct parameter
{
	char name[MAX_SIZE_SYMBOL];
	Type type;
	struct parameter *next;
} Parameter;

// Function symbol table entry
typedef struct functionEntry
{
	char name[MAX_SIZE_SYMBOL];
	Type returnType;
	Parameter *parameters;
	int paramCount;
	int isDefined; // 0 = only prototype, 1 = defined
	int isMain;		 // 1 if this is the main function
} FunctionEntry;

// Function symbol table node
typedef struct functionNode
{
	FunctionEntry data;
	struct functionNode *next;
} FunctionNode;

// Function symbol table
typedef struct functionTable
{
	FunctionNode *array;
	int max_size;
	int size;
} FunctionTable;

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
extern FunctionTable functionTable;

// Function prototypes

/**
 * @brief Initialize the symbol table
 * @param table Pointer to the symbol table structure
 * @return 1 on success, 0 on failure
 */
int initSymTable(SymTable *table);

/**
 * @brief Initialize the function table
 * @param table Pointer to the function table structure
 * @return 1 on success, 0 on failure
 */
int initFunctionTable(FunctionTable *table);

/**
 * @brief Print the contents of the symbol table
 * @param table Pointer to the symbol table structure
 */
void printSymTable(SymTable *table);

/**
 * @brief Print the contents of the function table
 * @param table Pointer to the function table structure
 */
void printFunctionTable(FunctionTable *table);

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
 * @brief Add a function prototype to the function table
 * @param table Pointer to the function table structure
 * @param name Function name
 * @param returnType Function return type
 * @param parameters List of parameters (can be NULL)
 * @param paramCount Number of parameters
 * @param isMain 1 if this is main function, 0 otherwise
 * @return 1 on success, 0 on failure
 */
int addFunctionPrototype(FunctionTable *table, char *name, Type returnType, Parameter *parameters, int paramCount, int isMain);

/**
 * @brief Mark a function as defined (implementation provided)
 * @param table Pointer to the function table structure
 * @param name Function name
 * @return 1 on success, 0 on failure
 */
int markFunctionDefined(FunctionTable *table, char *name);

/**
 * @brief Find a symbol in the table
 * @param table Pointer to the symbol table structure
 * @param identifier Variable name to search for
 * @return Pointer to symbol entry if found, NULL otherwise
 */
SymTableEntry *findSymTable(SymTable *table, char *identifier);

/**
 * @brief Find a function in the function table
 * @param table Pointer to the function table structure
 * @param name Function name to search for
 * @return Pointer to function entry if found, NULL otherwise
 */
FunctionEntry *findFunction(FunctionTable *table, char *name);

/**
 * @brief Create a new parameter
 * @param name Parameter name
 * @param type Parameter type
 * @return Pointer to new parameter, NULL on failure
 */
Parameter *createParameter(char *name, Type type);

/**
 * @brief Free parameter list
 * @param params Pointer to parameter list
 */
void freeParameters(Parameter *params);

/**
 * @brief Check if function call matches prototype
 * @param function Function entry
 * @param argTypes Array of argument types
 * @param argCount Number of arguments
 * @return 1 if compatible, 0 otherwise
 */
int checkFunctionCall(FunctionEntry *function, Type *argTypes, int argCount);

/**
 * @brief Free all memory allocated by the symbol table
 * @param table Pointer to the symbol table structure
 */
void freeSymTable(SymTable *table);

/**
 * @brief Free all memory allocated by the function table
 * @param table Pointer to the function table structure
 */
void freeFunctionTable(FunctionTable *table);

#endif