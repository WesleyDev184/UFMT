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
	if (table == NULL)
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
				const char *typeStr = (aux->data.type == INTEGER) ? "int" : (aux->data.type == REAL) ? "float"
																																														 : "string";
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

		strncpy(s, value, n);
		aux->data.value = s;
		aux->data.value[n] = '\0';

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
