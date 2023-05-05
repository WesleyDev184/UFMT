/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estatica x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 // Size of the hash table

// Structure for each entry in the hash table
typedef struct Entry
{
    char *key;          // Key of the entry
    char *value;        // Value of the entry
    struct Entry *next; // Pointer to the next entry in the linked list
} Entry;

// Structure for the hash table
typedef struct HashTable
{
    Entry **table; // Array of pointers to entry
    int size;      // Size of the table
} HashTable;

/**
 * The function calculates an index for a given key based on the sum of the ASCII values of its
 * characters, and returns the remainder of the division by a given table size.
 *
 * @param key A string representing the key for which the index needs to be calculated.
 * @param table_size The size of the hash table, which is the number of slots or buckets in the table
 * where key-value pairs can be stored.
 *
 * @return an integer value, which is the index calculated based on the given key and table size. This
 * index is used to determine the position of the key-value pair in a hash table.
 */
int calculate_index(char *key, int table_size)
{
    int index = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        index += key[i]; // Adds the ASCII value of each character in the key
    }
    return index % table_size; // Returns the remainder of the division by the table size
}

/**
 * The function creates a new entry with a given key and value, and returns a pointer to the new entry.
 *
 * @param key A string representing the key of the entry to be created.
 * @param value The value parameter is a string that represents the value associated with a key in a
 * key-value pair.
 *
 * @return The function `create_entry` is returning a pointer to a newly created `Entry` struct.
 */
Entry *create_entry(char *key, char *value)
{
    Entry *entry = malloc(sizeof(Entry)); // Allocates memory for a new entry
    entry->key = strdup(key);             // Copies the key to the entry using strdup (duplicates a string)
    entry->value = strdup(value);         // Copies the value to the entry
    entry->next = NULL;                   // Sets the pointer to the next entry as NULL
    return entry;                         // Returns the new entry created
}

/**
 * The insert function adds a new entry to a hash table at the calculated index based on the key.
 *
 * @param table a pointer to a HashTable struct, which contains an array of Entry pointers and the size
 * of the array.
 * @param key A string representing the key to be inserted into the hash table.
 * @param value The value parameter is a pointer to a character array representing the value to be
 * inserted into the hash table.
 */
void insert(HashTable *table, char *key, char *value)
{
    int index = calculate_index(key, table->size); // Calculates the table index for the key
    Entry *entry = create_entry(key, value);       // Creates a new entry
    entry->next = table->table[index];             // Sets the pointer of the new entry to the current entry in the index of the table
    table->table[index] = entry;                   // Sets the new entry as the current entry in the index of the table
}

/**
 * The function searches for a key in a hash table and returns its corresponding value if found.
 *
 * @param table a pointer to a HashTable struct, which contains an array of Entry pointers and the size
 * of the array.
 * @param key The key is a string that is used to search for a value in the hash table. It is the input
 * parameter for the search function.
 *
 * @return a pointer to the value associated with the provided key in the hash table. If the key is not
 * found in the hash table, the function returns NULL.
 */
char *search(HashTable *table, char *key)
{
    int index = calculate_index(key, table->size); // Calculates the table index for the key
    Entry *entry = table->table[index];            // Gets the current entry in the index of the table
    while (entry != NULL)
    { // Traverses the linked list of entries for that index
        if (strcmp(entry->key, key) == 0)
        {                                                                                               // Compares the key of the current entry with the provided key
            printf("Requested dictionary word:[%s] \n translation: [%s] \n", entry->key, entry->value); // Prints the key and value found
            return entry->value;                                                                        // Returns the found value
        }
        entry = entry->next; // Advances to the next entry in the linked list
    }
    return NULL; // Returns NULL if the key is not found in the hash table
}

/**
 * The function prints the contents of a hash table.
 *
 * @param table a pointer to a HashTable structure.
 */
void print_table(HashTable *table)
{
    printf("Hash Table:\n");
    for (int i = 0; i < table->size; i++)
    {

        Entry *entry = table->table[i];
        while (entry != NULL)
        {
            printf("[%s, %s]\n", entry->key, entry->value);
            entry = entry->next;
        }
        printf("\n");
    }
}

int main()
{
    HashTable table;
    table.size = TABLE_SIZE;
    table.table = calloc(TABLE_SIZE, sizeof(Entry *));

    insert(&table, "hello", "Olá");
    insert(&table, "goodbye", "Adeus");
    insert(&table, "thank you", "Obrigado");
    insert(&table, "good morning", "Bom dia");
    insert(&table, "good afternoon", "Boa tarde");
    insert(&table, "good night", "Boa noite");
    insert(&table, "how are you?", "como esta?");
    insert(&table, "what is your name?", "Como e seu nome?");
    insert(&table, "my name is", "Me chamo");
    insert(&table, "where are you from?", "De onde voce e?");

    print_table(&table);
    search(&table, "my name is");

    return 0;
}