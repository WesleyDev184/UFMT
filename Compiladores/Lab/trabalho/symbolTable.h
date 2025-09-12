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
#define MAX_SCOPE_DEPTH 50

typedef enum
{
	INTEGER,
	FLOAT,
	STRING,
	CHAR,
	BOOL
} Type;

typedef enum
{
	SCOPE_GLOBAL,		// Escopo global (nivel 0)
	SCOPE_FUNCTION, // Escopo de função (nivel 1)
	SCOPE_BLOCK			// Escopo de bloco (if, while, etc - nivel 2+)
} ScopeType;

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

// Data type declaration (mantido para compatibilidade)
struct symTableEntry
{
	char identifier[MAX_SIZE_SYMBOL];
	Type type;
	char *value;
	int len_value;
};
typedef struct symTableEntry SymTableEntry;

// Data type declaration for scoped symbol table
struct scopedSymTableEntry
{
	char identifier[MAX_SIZE_SYMBOL];
	Type type;
	char *value;
	int len_value;
	int scopeLevel;			 // Nivel do escopo (0=global, 1=função, 2+=bloco)
	ScopeType scopeType; // Tipo do escopo
	int isParameter;		 // 1 se for parâmetro de função, 0 caso contrário
};
typedef struct scopedSymTableEntry ScopedSymTableEntry;

// Node for scoped symbol table
struct scopedSymTableNode
{
	ScopedSymTableEntry data;
	struct scopedSymTableNode *next;
};
typedef struct scopedSymTableNode ScopedSymTableNode;

// Scope information
struct scopeInfo
{
	int level;													// Nivel do escopo
	ScopeType type;											// Tipo do escopo
	char functionName[MAX_SIZE_SYMBOL]; // Nome da função (se aplicável)
	struct scopeInfo *parent;						// Escopo pai
};
typedef struct scopeInfo ScopeInfo;

// Scoped symbol table with scope management
struct scopedSymTable
{
	ScopedSymTableNode *array;
	int max_size;
	int size;
	ScopeInfo *currentScope;				 // Escopo atual
	int scopeStack[MAX_SCOPE_DEPTH]; // Pilha de níveis de escopo
	int stackTop;										 // Topo da pilha
};
typedef struct scopedSymTable ScopedSymTable;

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
extern ScopedSymTable scopedTable; // Nova tabela com escopo

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

// ===============================================
// SCOPED SYMBOL TABLE FUNCTIONS
// ===============================================

/**
 * @brief Initialize the scoped symbol table
 * @param table Pointer to the scoped symbol table structure
 * @return 1 on success, 0 on failure
 */
int initScopedSymTable(ScopedSymTable *table);

/**
 * @brief Enter a new scope
 * @param table Pointer to the scoped symbol table structure
 * @param scopeType Type of scope being entered
 * @param functionName Name of function (if entering function scope)
 * @return 1 on success, 0 on failure
 */
int enterScope(ScopedSymTable *table, ScopeType scopeType, const char *functionName);

/**
 * @brief Exit current scope
 * @param table Pointer to the scoped symbol table structure
 * @return 1 on success, 0 on failure
 */
int exitScope(ScopedSymTable *table);

/**
 * @brief Add a symbol to the current scope
 * @param table Pointer to the scoped symbol table structure
 * @param identifier Variable name
 * @param type Variable type
 * @param value Initial value (can be NULL)
 * @param isParameter 1 if it's a function parameter, 0 otherwise
 * @return 1 on success, 0 on failure
 */
int addScopedSymbol(ScopedSymTable *table, char *identifier, Type type, char *value, int isParameter);

/**
 * @brief Find a symbol in current scope and parent scopes (scope resolution)
 * @param table Pointer to the scoped symbol table structure
 * @param identifier Variable name to search for
 * @return Pointer to symbol entry if found, NULL otherwise
 */
ScopedSymTableEntry *findScopedSymbol(ScopedSymTable *table, char *identifier);

/**
 * @brief Check if symbol exists in current scope only
 * @param table Pointer to the scoped symbol table structure
 * @param identifier Variable name to search for
 * @return Pointer to symbol entry if found in current scope, NULL otherwise
 */
ScopedSymTableEntry *findSymbolInCurrentScope(ScopedSymTable *table, char *identifier);

/**
 * @brief Add function parameters as symbols in function scope
 * @param table Pointer to the scoped symbol table structure
 * @param parameters List of function parameters
 * @return 1 on success, 0 on failure
 */
int addFunctionParameters(ScopedSymTable *table, Parameter *parameters);

/**
 * @brief Print the contents of the scoped symbol table
 * @param table Pointer to the scoped symbol table structure
 */
void printScopedSymTable(ScopedSymTable *table);

/**
 * @brief Get current scope level
 * @param table Pointer to the scoped symbol table structure
 * @return Current scope level
 */
int getCurrentScopeLevel(ScopedSymTable *table);

/**
 * @brief Free all memory allocated by the scoped symbol table
 * @param table Pointer to the scoped symbol table structure
 */
void freeScopedSymTable(ScopedSymTable *table);

/**
 * @brief Search for symbol using scope resolution and fallback to global table
 * @param scopedTable Pointer to the scoped symbol table structure
 * @param globalTable Pointer to the global symbol table structure
 * @param identifier Variable name to search for
 * @param foundType Pointer to store the type if found (output parameter)
 * @param isFromGlobal Pointer to flag indicating if found in global table (output parameter)
 * @return 1 if found, 0 if not found
 */
int findSymbolHybrid(ScopedSymTable *scopedTable, SymTable *globalTable, char *identifier, Type *foundType, int *isFromGlobal);

/**
 * @brief Parse parameter string and create parameter list
 * @param paramString String containing parameters in format "type name,type name,..."
 * @param paramCount Pointer to store the number of parameters (output parameter)
 * @return Pointer to parameter list, NULL on error
 */
Parameter *parseParameterString(char *paramString, int *paramCount);

/**
 * @brief Free parameter list
 * @param parameters Pointer to parameter list to free
 */
void freeParameters(Parameter *parameters);

#endif