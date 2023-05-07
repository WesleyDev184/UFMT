/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tabuleiro.c"
#include "Jogador.c"

LinkedList *createCircularBoard(char *filename)
{
    FILE *fp;
    int size, value, values[26];
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Lê o tamanho da lista na primeira linha do arquivo
    fscanf(fp, "%d", &size);

    // Lê os valores do arquivo e adiciona na lista
    for (int i = 0; i < size; i++)
    {
        fscanf(fp, "%d", &value);
        values[i] = value;
    }

    list = createList(size, values);

    fclose(fp);

    return list;
}

ListPlayer *createCircularPlayer(char *filename)
{
    FILE *file;
    int size;

    // Abre o file para leitura
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o file\n");
        return 1;
    }

    // Lê o size do array do file
    fscanf(file, "%d", &size);

    char strings[size][50];
    ListPlayer *list = createPlayerList(size);

    // Fecha o file
    fclose(file);

    return list;
}

void Game()
{
    LinkedList *board = createCircularBoard("defineBoard.txt");
    printList(board);

    ListPlayer *players = createCircularPlayer("definePlayer.txt");
    printPlayerList(players);

    NodePLayer *current_player = players->head; // Começa com o primeiro jogador
    Node *current_position = board->head;       // Começa na posição inicial do tabuleiro

    srand(time(NULL));

    while (1)
    {
        if (players->head == NULL)
        {
            printf("Todos os jogadores foram destruidos\n");
            break;
        }

        printf("Vez do jogador %c\n", current_player->id);

        if (current_player->position != NULL)
        {
            while (current_position->id != current_player->position)
            {
                current_position = current_position->next;
            }
        }

        int roll = rand() % 6 + 1; // Sorteia o valor do dado
        printf("O jogador %c jogou o dado e tirou %d\n", current_player->id, roll);

        // Move o jogador na lista do tabuleiro
        if (current_position->data < 0)
        {
            for (int i = 0; i < roll; i++)
            {
                current_position = current_position->prev;
                if (current_position == NULL)
                {
                    current_position = board->head;
                }
            }
        }
        else
        {
            for (int i = 0; i < roll; i++)
            {
                current_position = current_position->next;
                if (current_position == NULL)
                {
                    current_position = board->head;
                }
            }
        }

        printf("O jogador %c esta na posicao %c\n", current_player->id, current_position->id);

        current_player->data += current_position->data;

        if (current_player->data <= 0)
        {
            NodePLayer *temp = current_player->next;
            destroyPlayer(players, current_player->id);
            printf("O jogador foi destruido\n");
            printf("\n");
            current_player = temp;
        }
        else
        {
            printf("O jogador %c tem %d pontos\n\n", current_player->id, current_player->data);
            setPosition(players, current_player->id, current_position->id);
            current_player = current_player->next;
            current_position = board->head;
        }

        printPlayerList(players);
        printf("\n");

        if (players->head == players->rear)
        {
            printf("O jogador %c venceu o jogo com %d pontos!\n", players->head->id, players->head->data);
            break;
        }
    }
}

int main()
{
    Game();
    return 0;
}
