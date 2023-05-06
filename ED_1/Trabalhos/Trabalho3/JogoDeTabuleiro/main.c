/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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

ListPlayers* createCircularListPlayers(char* filename) {
    FILE* fp;
    int size;
    char** players;
    ListPlayers* listOfPlayers = NULL;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Lê o tamanho da lista na primeira linha do arquivo
    if (fscanf(fp, "%d", &size) != 1) {
        printf("Erro ao ler o tamanho da lista.\n");
        fclose(fp);
        return NULL;
    }

    // Aloca o array de ponteiros
    players = (char**)malloc(size * sizeof(char*));
    if (players == NULL) {
        printf("Erro ao alocar a memória para o array de ponteiros.\n");
        fclose(fp);
        return NULL;
    }

    // Lê os valores do arquivo e adiciona na lista
    for (int i = 0; i < size; i++) {
        char buffer[101];
        if (fscanf(fp, "%100s", buffer) != 1) {
            printf("Erro ao ler o valor na linha %d.\n", i+2);
            fclose(fp);
            free(players);
            destroyPlayerList(listOfPlayers);
            return NULL;
        }else{
        printf("Leu a linha %d\n",i+2);
        }
        players[i] = strdup(buffer);

        printf("valor %s\n", players[i]);

        if (players[i] == NULL) {
            printf("Erro ao alocar a memória para o valor na linha %d.\n", i+2);
            fclose(fp);
            for (int j = 0; j < i; j++) {
                free(players[j]);
            }
            free(players);
            destroyPlayerList(listOfPlayers);
            return NULL;
        }
    }

    listOfPlayers = createPlayerList(size, players);
    if (listOfPlayers == NULL) {
        printf("Erro ao criar a lista de jogadores.\n");
        fclose(fp);
        for (int i = 0; i < size; i++) {
            free(players[i]);
        }
        free(players);
        return NULL;
    }

    fclose(fp);
    free(players);

    return listOfPlayers;
}


int rollDice() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com a hora atual
    return rand() % 6 + 1; // Retorna um número aleatório entre 1 e 6
}

void Game(){
    LinkedList *board = createCircularBoard("defineBoard.txt");
    printList(board);

    ListPlayers *players = createCircularListPlayers("definePlayer.txt");
    printListPlayer(players);

    NodePlayer *current_player = players->head; // Começa com o primeiro jogador
    Node *current_position = board->head; // Começa na posição inicial do tabuleiro

    printf("test\n");


    // Realiza as jogadas
    // while (1) {
    //     int roll = rollDice(); // Sorteia o valor do dado
    //     printf("%s jogou o dado e tirou %d\n", current_player->id, roll);

    //     // Move o jogador na lista circular
    //     for (int i = 0; i < roll; i++) {
    //         current_player = current_player->next;
    //     }

    //     // Move o jogador na lista do tabuleiro
    //     for (int i = 0; i < roll; i++) {
    //         current_position = current_position->next;
    //         if (current_position == NULL) { // Se chegou ao final do tabuleiro, volta para o início
    //             current_position = board->head;
    //         }
    //     }

    //     printf("%s está na posição %d\n", current_player->id, current_position->id);

    //     // Verifica se o jogador venceu
    //     if (current_position->id == board->rear->data) {
    //         printf("%s venceu!\n", current_player->id);
    //         break;
    //     }
    // }
}

int main()
{
    /*

    int num;

    srand(time(NULL));

    num = rand() % 6 + 1;
    */

    Game();
    return 0;
}
