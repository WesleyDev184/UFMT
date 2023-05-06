#ifndef JOGADORES_C
#define JOGADORES_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodePlayer {
    char *id;
    int data;
    struct nodePlayer *next;
} NodePlayer;

typedef struct listPlayers {
    NodePlayer *head;
    NodePlayer *rear;
} ListPlayers;

/**
 * This function creates a singly linked list with nodes containing data and an ID.
 *
 * @param size The size parameter is an integer that represents the number of elements in the linked
 * list that will be created.
 * @param values An array of strings containing the IDs to be stored in the linked list.
 *
 * @return The function `createPlayerList` returns a pointer to a `ListPlayers` structure.
 */

ListPlayers *createPlayerList(int size, char **values) {
    if (size == 0 || values == NULL) {
        return NULL;
    }

    ListPlayers *l = (ListPlayers *) malloc(sizeof(ListPlayers));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->rear = NULL;

    NodePlayer *new_node = NULL;
    NodePlayer *current_node = NULL;
    size_t id_size = 0;
    for (int i = 0; i < size; i++) {
        id_size = strlen(values[i]) + 1;
        new_node = (NodePlayer *) calloc(1, sizeof(NodePlayer) + id_size);
        if (new_node == NULL) {
            return NULL;
        }
        new_node->id = (char *) (new_node + 1);
        strcpy(new_node->id, values[i]);
        new_node->data = 0;
        new_node->next = NULL;

        if (l->head == NULL) {
            l->head = new_node;
            l->rear = new_node;
            current_node = new_node;
        } else {
            current_node->next = new_node;
            current_node = new_node;
        }
    }
    l->rear->next = l->head;

    return l;
}


void destroyPlayerList(ListPlayers *list) {
    // Percorre a lista e libera a memória alocada para cada nó e para cada string no campo 'id'
    NodePlayer *current = list->head;
    while (current != NULL) {
        NodePlayer *next = current->next;
        free(current->id);
        free(current);
        current = next;
    }

    // Libera a memória alocada para a estrutura da lista
    free(list);
}


void printListPlayer(ListPlayers *list) {
    printf("Players: \n");

    NodePlayer *current = list->head;

    while (current != list->rear) {
        printf("%s ", current->id);
        printf("%d ", current->data);
        current = current->next;
        printf("\n");
    }
    printf("%s ", current->id);
    printf("%d ", current->data);
    printf("\n");
}

#endif
