/*
 *
 * UFMT - Universidade Federal de Mato Grosso
 * Laboratório de Compiladores
 * Author: Wesley Antonio Junior dos Santos
 * RGA:202011722024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"

// Global symbol table instances
ScopedSymTable scopedTable;

// Hash function
int hashFunction(int max_size, char *key)
{
	int i = 0;
	int sum = 0;
	int factor = 0;
	while (key[i] != '\0')
	{
		sum += (key[i] + factor);
		factor += 113;
		i++;
	}

	return sum % max_size;

	// Multiplicative method
	// double a = 0.6180339887; // Knuth's constant
	// a *= sum;
	// a = a - (int) a;
	// return (int)(a * max_size);
}

// Function that initializes Hash table, putting -1 in all numbers
int initSymTable(SymTable *table)
{
	table->size = 0;
	table->max_size = MAX_SIZE_HASH_ARRAY;

	table->array = (SymTableNode *)malloc(table->max_size * sizeof(SymTableNode));
	if (table->array == NULL)
		return 0;

	// Initialize each position of the array
	for (int i = 0; i < table->max_size; i++)
	{
		table->array[i].data.identifier[0] = '\0';
		table->array[i].data.value = NULL;
		table->array[i].data.len_value = 0;

		table->array[i].next = NULL;
	}

	return 1;
}

// Function that prints the Hash table
// Function that prints the Hash table
void printSymTable(SymTable *table)
{
	int i = 0;
	int hasEntries = 0;

	// First, check if there are any entries
	for (i = 0; i < table->max_size; i++)
	{
		if (table->array[i].data.identifier[0] != '\0')
		{
			hasEntries = 1;
			break;
		}
	}

	printf("\n=== SYMBOL TABLE ===\n");

	if (!hasEntries)
	{
		printf("Symbol table is empty.\n");
		return;
	}

	printf("%-5s %-15s %-8s %-10s\n", "Hash", "Identifier", "Type", "Value");
	printf("%-5s %-15s %-8s %-10s\n", "----", "----------", "----", "-----");

	for (i = 0; i < table->max_size; i++)
	{
		// Only print non-empty entries
		if (table->array[i].data.identifier[0] != '\0')
		{
			SymTableNode *aux = &table->array[i];

			while (aux != NULL)
			{
				const char *typeStr;
				switch (aux->data.type)
				{
				case INTEGER:
					typeStr = "int";
					break;
				case FLOAT:
					typeStr = "float";
					break;
				case STRING:
					typeStr = "string";
					break;
				case CHAR:
					typeStr = "char";
					break;
				case BOOL:
					typeStr = "bool";
					break;
				default:
					typeStr = "unknown";
					break;
				}
				const char *valueStr = (aux->data.value != NULL) ? aux->data.value : "uninitialized";

				printf("%-5d %-15s %-8s %-10s\n", i,
							 aux->data.identifier, typeStr, valueStr);

				aux = aux->next;
			}
		}
	}
}

// Hash table insertion function
int addSymTable(SymTable *table, char *identifier, Type type, char *value)
{
	int pos;
	pos = hashFunction(table->max_size, identifier);

	SymTableNode *aux = NULL;

	// Check if position is free
	if (table->array[pos].data.identifier[0] == '\0')
		aux = &table->array[pos];

	else
	{
		// Check if it's not already repeated data
		aux = &table->array[pos];
		while (aux != NULL && strcmp(aux->data.identifier, identifier) != 0)
			aux = aux->next;
		if (aux != NULL)
			return 0;

		aux = (SymTableNode *)malloc(sizeof(SymTableNode));
		if (aux == NULL)
			return 0;

		// The table now points to the allocated aux,
		// so it will always be inserted at the beginning and "push the list"
		aux->next = table->array[pos].next;
		table->array[pos].next = aux;
	}

	// Identifier
	strncpy(aux->data.identifier, identifier, MAX_SIZE_SYMBOL - 1);
	aux->data.identifier[MAX_SIZE_SYMBOL - 1] = '\0';

	// Type
	aux->data.type = type;

	// Value
	if (value != NULL)
	{
		int n = strlen(value);
		char *s = (char *)malloc((n + 1) * sizeof(char));
		if (s == NULL)
			return 0;

		// Use strcpy instead of strncpy to avoid truncation warning
		strcpy(s, value);
		aux->data.value = s;

		// Length of the value string
		aux->data.len_value = n;
	}

	table->size += 1;

	return 1;
}

// Function that searches for the value in the hash table
SymTableEntry *findSymTable(SymTable *table, char *identifier)
{
	int pos = hashFunction(table->max_size, identifier); // position where it was inserted

	SymTableNode *aux;
	aux = &(table->array[pos]);

	while ((aux != NULL) && (strcmp(aux->data.identifier, identifier) != 0))
		aux = aux->next;

	// It will stop because it didn't reach null and didn't find.
	if (aux == NULL)
		return NULL;
	else
		return &aux->data;
}

// Function that frees all memory allocated by the table and reinitializes it
void freeSymTable(SymTable *table)
{
	SymTableNode *node;
	SymTableNode *aux;
	for (int i = 0; i < table->max_size; i++)
	{
		aux = NULL;
		node = &table->array[i];
		if (node->data.identifier[0] != '\0')
		{
			free(node->data.value);
			node = node->next;

			while (node != NULL)
			{
				aux = node;
				node = node->next;

				free(aux->data.value);
				free(aux);
			}
		}
	}
	free(table->array);
}

// ===============================================
// FUNCTION TABLE IMPLEMENTATION
// ===============================================

// Initialize function table
int initFunctionTable(FunctionTable *table)
{
	table->size = 0;
	table->max_size = MAX_SIZE_HASH_ARRAY;

	table->array = (FunctionNode *)malloc(table->max_size * sizeof(FunctionNode));
	if (table->array == NULL)
		return 0;

	// Initialize each position of the array
	for (int i = 0; i < table->max_size; i++)
	{
		table->array[i].data.name[0] = '\0';
		table->array[i].data.parameters = NULL;
		table->array[i].data.paramCount = 0;
		table->array[i].data.isDefined = 0;
		table->array[i].data.isMain = 0;
		table->array[i].next = NULL;
	}

	return 1;
}

// Print function table
void printFunctionTable(FunctionTable *table)
{
	int i = 0;
	int hasEntries = 0;

	// First, check if there are any entries
	for (i = 0; i < table->max_size; i++)
	{
		if (table->array[i].data.name[0] != '\0')
		{
			hasEntries = 1;
			break;
		}
	}

	if (!hasEntries)
	{
		printf("Function table is empty.\n");
		return;
	}

	printf("\n=== FUNCTION TABLE ===\n");
	printf("%-15s %-10s %-8s %-12s %-20s\n", "Function", "ReturnType", "Params", "Status", "Parameters");
	printf("%-15s %-10s %-8s %-12s %-20s\n", "--------", "----------", "------", "------", "----------");

	for (i = 0; i < table->max_size; i++)
	{
		if (table->array[i].data.name[0] != '\0')
		{
			FunctionNode *aux = &table->array[i];

			while (aux != NULL)
			{
				const char *typeStr;
				switch (aux->data.returnType)
				{
				case INTEGER:
					typeStr = "int";
					break;
				case FLOAT:
					typeStr = "float";
					break;
				case STRING:
					typeStr = "string";
					break;
				case CHAR:
					typeStr = "char";
					break;
				case BOOL:
					typeStr = "bool";
					break;
				default:
					typeStr = "unknown";
					break;
				}

				const char *statusStr = aux->data.isDefined ? "defined" : "prototype";
				if (aux->data.isMain)
					statusStr = "main";

				printf("%-15s %-10s %-8d %-12s ",
							 aux->data.name, typeStr, aux->data.paramCount, statusStr);

				// Print parameters
				Parameter *param = aux->data.parameters;
				if (param == NULL)
				{
					printf("(void)");
				}
				else
				{
					printf("(");
					while (param != NULL)
					{
						const char *paramTypeStr;
						switch (param->type)
						{
						case INTEGER:
							paramTypeStr = "int";
							break;
						case FLOAT:
							paramTypeStr = "float";
							break;
						case STRING:
							paramTypeStr = "string";
							break;
						case CHAR:
							paramTypeStr = "char";
							break;
						case BOOL:
							paramTypeStr = "bool";
							break;
						default:
							paramTypeStr = "unknown";
							break;
						}
						printf("%s %s", paramTypeStr, param->name);
						param = param->next;
						if (param != NULL)
							printf(", ");
					}
					printf(")");
				}
				printf("\n");

				aux = aux->next;
			}
		}
	}
}

// Add function prototype
int addFunctionPrototype(FunctionTable *table, char *name, Type returnType, Parameter *parameters, int paramCount, int isMain)
{
	int pos = hashFunction(table->max_size, name);
	FunctionNode *aux = NULL;

	// Check if position is free
	if (table->array[pos].data.name[0] == '\0')
		aux = &table->array[pos];
	else
	{
		// Check if it's not already repeated data
		aux = &table->array[pos];
		while (aux != NULL && strcmp(aux->data.name, name) != 0)
			aux = aux->next;
		if (aux != NULL)
			return 0; // Function already exists

		aux = (FunctionNode *)malloc(sizeof(FunctionNode));
		if (aux == NULL)
			return 0;

		aux->next = table->array[pos].next;
		table->array[pos].next = aux;
	}

	// Function name
	strncpy(aux->data.name, name, MAX_SIZE_SYMBOL - 1);
	aux->data.name[MAX_SIZE_SYMBOL - 1] = '\0';

	// Return type
	aux->data.returnType = returnType;

	// Parameters
	aux->data.parameters = parameters;
	aux->data.paramCount = paramCount;
	aux->data.isDefined = 0;
	aux->data.isMain = isMain;

	table->size += 1;
	return 1;
}

// Mark function as defined
int markFunctionDefined(FunctionTable *table, char *name)
{
	FunctionEntry *func = findFunction(table, name);
	if (func == NULL)
		return 0;

	func->isDefined = 1;
	return 1;
}

// Find function in table
FunctionEntry *findFunction(FunctionTable *table, char *name)
{
	int pos = hashFunction(table->max_size, name);
	FunctionNode *aux = &(table->array[pos]);

	while ((aux != NULL) && (strcmp(aux->data.name, name) != 0))
		aux = aux->next;

	if (aux == NULL)
		return NULL;
	else
		return &aux->data;
}

// Create new parameter
Parameter *createParameter(char *name, Type type)
{
	Parameter *param = (Parameter *)malloc(sizeof(Parameter));
	if (param == NULL)
		return NULL;

	strncpy(param->name, name, MAX_SIZE_SYMBOL - 1);
	param->name[MAX_SIZE_SYMBOL - 1] = '\0';
	param->type = type;
	param->next = NULL;

	return param;
}

// Free parameter list
void freeParameters(Parameter *params)
{
	Parameter *current = params;
	while (current != NULL)
	{
		Parameter *next = current->next;
		free(current);
		current = next;
	}
}

// Check function call compatibility
int checkFunctionCall(FunctionEntry *function, Type *argTypes, int argCount)
{
	if (function->paramCount != argCount)
		return 0;

	Parameter *param = function->parameters;
	for (int i = 0; i < argCount; i++)
	{
		if (param == NULL || param->type != argTypes[i])
			return 0;
		param = param->next;
	}

	return 1;
}

// Free function table
void freeFunctionTable(FunctionTable *table)
{
	FunctionNode *node;
	FunctionNode *aux;
	for (int i = 0; i < table->max_size; i++)
	{
		aux = NULL;
		node = &table->array[i];
		if (node->data.name[0] != '\0')
		{
			freeParameters(node->data.parameters);
			node = node->next;

			while (node != NULL)
			{
				aux = node;
				node = node->next;

				freeParameters(aux->data.parameters);
				free(aux);
			}
		}
	}
	free(table->array);
}

// //Função que libera toda a mémoria alocada pela tabela e reinicializa ela
// void liberaTabela(SymTableNode* tab)
// {
//     SymTableNode* p,* ant;
//     int i;

//     for (i = 0; i < TAMTABELA; i++)
//     {
//         p = tab[i].next;
//         while (p != NULL)
//         {
//             ant = p;
//             p = p->next;
//             free(ant);
//         }

//         tab[i].dados.numero = -1;
//         tab[i].next = NULL;
//     }
// }

// ===============================================
// SCOPED SYMBOL TABLE IMPLEMENTATION
// ===============================================

// Initialize scoped symbol table
int initScopedSymTable(ScopedSymTable *table)
{
	table->size = 0;
	table->max_size = MAX_SIZE_HASH_ARRAY;
	table->currentScope = NULL;
	table->stackTop = -1;

	table->array = (ScopedSymTableNode *)malloc(table->max_size * sizeof(ScopedSymTableNode));
	if (table->array == NULL)
		return 0;

	// Initialize each position of the array
	for (int i = 0; i < table->max_size; i++)
	{
		table->array[i].data.identifier[0] = '\0';
		table->array[i].data.value = NULL;
		table->array[i].data.len_value = 0;
		table->array[i].data.scopeLevel = -1;
		table->array[i].data.isParameter = 0;
		table->array[i].next = NULL;
	}

	// Enter global scope automatically
	return enterScope(table, SCOPE_GLOBAL, NULL);
}

// Enter a new scope
int enterScope(ScopedSymTable *table, ScopeType scopeType, const char *functionName)
{
	if (table->stackTop >= MAX_SCOPE_DEPTH - 1)
	{
		fprintf(stderr, "Error: Maximum scope depth exceeded\n");
		return 0;
	}

	// Create new scope info
	ScopeInfo *newScope = (ScopeInfo *)malloc(sizeof(ScopeInfo));
	if (newScope == NULL)
		return 0;

	// Set scope level
	if (table->currentScope == NULL)
	{
		newScope->level = 0; // Global scope
	}
	else
	{
		newScope->level = table->currentScope->level + 1;
	}

	newScope->type = scopeType;
	newScope->parent = table->currentScope;

	// Set function name if provided
	if (functionName != NULL)
	{
		strncpy(newScope->functionName, functionName, MAX_SIZE_SYMBOL - 1);
		newScope->functionName[MAX_SIZE_SYMBOL - 1] = '\0';
	}
	else
	{
		newScope->functionName[0] = '\0';
	}

	// Update scope stack
	table->stackTop++;
	table->scopeStack[table->stackTop] = newScope->level;
	table->currentScope = newScope;

	return 1;
}

// Exit current scope
int exitScope(ScopedSymTable *table)
{
	if (table->currentScope == NULL || table->stackTop < 0)
	{
		fprintf(stderr, "Error: No scope to exit\n");
		return 0;
	}

	ScopeInfo *oldScope = table->currentScope;
	table->currentScope = oldScope->parent;
	table->stackTop--;

	free(oldScope);
	return 1;
}

// Add symbol to current scope
int addScopedSymbol(ScopedSymTable *table, char *identifier, Type type, char *value, int isParameter)
{
	if (table->currentScope == NULL)
	{
		fprintf(stderr, "Error: No current scope\n");
		return 0;
	}

	// Check if symbol already exists in current scope
	if (findSymbolInCurrentScope(table, identifier) != NULL)
	{
		return 0; // Symbol already exists in current scope
	}

	int hash = hashFunction(table->max_size, identifier);
	ScopedSymTableNode *node = &table->array[hash];

	// Create new entry
	ScopedSymTableEntry newEntry;
	strncpy(newEntry.identifier, identifier, MAX_SIZE_SYMBOL - 1);
	newEntry.identifier[MAX_SIZE_SYMBOL - 1] = '\0';
	newEntry.type = type;
	newEntry.scopeLevel = table->currentScope->level;
	newEntry.scopeType = table->currentScope->type;
	newEntry.isParameter = isParameter;

	// Handle value
	if (value != NULL)
	{
		newEntry.len_value = strlen(value);
		newEntry.value = (char *)malloc((newEntry.len_value + 1) * sizeof(char));
		if (newEntry.value == NULL)
			return 0;
		strcpy(newEntry.value, value);
	}
	else
	{
		newEntry.value = NULL;
		newEntry.len_value = 0;
	}

	// Insert in hash table
	if (node->data.identifier[0] == '\0')
	{
		// First entry at this hash position
		node->data = newEntry;
	}
	else
	{
		// Collision - add at end of chain
		while (node->next != NULL)
		{
			node = node->next;
		}

		ScopedSymTableNode *newNode = (ScopedSymTableNode *)malloc(sizeof(ScopedSymTableNode));
		if (newNode == NULL)
		{
			if (newEntry.value != NULL)
				free(newEntry.value);
			return 0;
		}

		newNode->data = newEntry;
		newNode->next = NULL;
		node->next = newNode;
	}

	table->size++;
	return 1;
}

// Find symbol in current scope only
ScopedSymTableEntry *findSymbolInCurrentScope(ScopedSymTable *table, char *identifier)
{
	if (table->currentScope == NULL)
		return NULL;

	int hash = hashFunction(table->max_size, identifier);
	ScopedSymTableNode *node = &table->array[hash];

	while (node != NULL && node->data.identifier[0] != '\0')
	{
		if (strcmp(node->data.identifier, identifier) == 0 &&
				node->data.scopeLevel == table->currentScope->level)
		{
			return &node->data;
		}
		node = node->next;
	}

	return NULL;
}

// Find symbol with scope resolution (current scope first, then parent scopes)
ScopedSymTableEntry *findScopedSymbol(ScopedSymTable *table, char *identifier)
{
	// Validate input parameters
	if (table == NULL || identifier == NULL || table->array == NULL)
	{
		return NULL;
	}

	// Start from current scope and go up the scope chain
	ScopeInfo *scope = table->currentScope;

	while (scope != NULL)
	{
		int hash = hashFunction(table->max_size, identifier);
		ScopedSymTableNode *node = &table->array[hash];

		while (node != NULL && node->data.identifier[0] != '\0')
		{
			if (strcmp(node->data.identifier, identifier) == 0 &&
					node->data.scopeLevel == scope->level)
			{
				return &node->data;
			}
			node = node->next;
		}

		scope = scope->parent;
	}

	return NULL;
}

// Add function parameters as symbols
int addFunctionParameters(ScopedSymTable *table, Parameter *parameters)
{
	Parameter *param = parameters;
	while (param != NULL)
	{
		if (!addScopedSymbol(table, param->name, param->type, NULL, 1))
		{
			fprintf(stderr, "Error: Failed to add parameter '%s' to scope\n", param->name);
			return 0;
		}
		param = param->next;
	}
	return 1;
}

// Get current scope level
int getCurrentScopeLevel(ScopedSymTable *table)
{
	if (table == NULL || table->currentScope == NULL)
		return -1;
	return table->currentScope->level;
}

// Print scoped symbol table
void printScopedSymTable(ScopedSymTable *table)
{
	printf("\n=== SCOPED SYMBOL TABLE ===\n");
	printf("Current Scope Level: %d\n", getCurrentScopeLevel(table));
	printf("%-15s %-8s %-8s %-5s %-10s %-10s\n", "Identifier", "Type", "Scope", "Level", "IsParam", "Value");
	printf("%-15s %-8s %-8s %-5s %-10s %-10s\n", "----------", "----", "-----", "-----", "-------", "-----");

	for (int i = 0; i < table->max_size; i++)
	{
		ScopedSymTableNode *node = &table->array[i];
		while (node != NULL && node->data.identifier[0] != '\0')
		{
			const char *typeStr;
			const char *scopeStr;

			switch (node->data.type)
			{
			case INTEGER:
				typeStr = "int";
				break;
			case FLOAT:
				typeStr = "float";
				break;
			case CHAR:
				typeStr = "char";
				break;
			case BOOL:
				typeStr = "bool";
				break;
			case STRING:
				typeStr = "string";
				break;
			default:
				typeStr = "unknown";
			}

			switch (node->data.scopeType)
			{
			case SCOPE_GLOBAL:
				scopeStr = "global";
				break;
			case SCOPE_FUNCTION:
				scopeStr = "function";
				break;
			case SCOPE_BLOCK:
				scopeStr = "block";
				break;
			default:
				scopeStr = "unknown";
			}

			printf("%-15s %-8s %-8s %-5d %-10s %-10s\n",
						 node->data.identifier,
						 typeStr,
						 scopeStr,
						 node->data.scopeLevel,
						 node->data.isParameter ? "yes" : "no",
						 node->data.value ? node->data.value : "NULL");

			node = node->next;
		}
	}
}

// Free scoped symbol table
void freeScopedSymTable(ScopedSymTable *table)
{
	// Exit all scopes
	while (table->currentScope != NULL)
	{
		exitScope(table);
	}

	// Free all symbol entries
	for (int i = 0; i < table->max_size; i++)
	{
		ScopedSymTableNode *node = &table->array[i];
		if (node->data.identifier[0] != '\0')
		{
			if (node->data.value != NULL)
				free(node->data.value);

			ScopedSymTableNode *next = node->next;
			while (next != NULL)
			{
				ScopedSymTableNode *temp = next;
				next = next->next;
				if (temp->data.value != NULL)
					free(temp->data.value);
				free(temp);
			}
		}
	}

	free(table->array);
	table->array = NULL;
	table->size = 0;
}

// Search for symbol using scope resolution and fallback to global table
int findSymbolHybrid(ScopedSymTable *scopedTable, SymTable *globalTable, char *identifier, Type *foundType, int *isFromGlobal)
{
	// Validate input parameters
	if (scopedTable == NULL || globalTable == NULL || identifier == NULL || foundType == NULL || isFromGlobal == NULL)
	{
		fprintf(stderr, "DEBUG: Null parameter in findSymbolHybrid\n");
		return 0;
	}

	// First, try to find in scoped table (only if we have an active scope beyond global)
	if (scopedTable->currentScope != NULL && scopedTable->currentScope->level > 0)
	{
		ScopedSymTableEntry *scopedEntry = findScopedSymbol(scopedTable, identifier);
		if (scopedEntry != NULL)
		{
			*foundType = scopedEntry->type;
			*isFromGlobal = 0;
			return 1;
		}
	}

	// If not found in scoped table, try global table
	SymTableEntry *globalEntry = findSymTable(globalTable, identifier);
	if (globalEntry != NULL)
	{
		*foundType = globalEntry->type;
		*isFromGlobal = 1;
		return 1;
	}

	// Not found in either table
	fprintf(stderr, "DEBUG: Symbol '%s' not found in either table\n", identifier);
	return 0;
}

// Optimized hash function using djb2 algorithm
int optimizedHashFunction(int table_size, char *identifier)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *identifier++))
	{
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}

	return hash % table_size;
}
