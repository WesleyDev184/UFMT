#include <stdio.h>
#include <math.h>

// Definindo a estrutura do ponto
typedef struct tipo_ponto {
    float x;
    float y;
} tipo_ponto;

// Definindo a estrutura da linha
typedef struct tipo_linha {
    tipo_ponto p1;
    tipo_ponto p2;
} tipo_linha;

// Função para calcular a distância entre dois pontos
float distancia(tipo_ponto p1, tipo_ponto p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}

// Função para carregar os dados dos pontos a partir de um arquivo
void carrega_pontos(FILE* arquivo, tipo_ponto* p1, tipo_ponto* p2) {
    fscanf(arquivo, "%f %f %f %f", &p1->x, &p1->y, &p2->x, &p2->y);
}

// Função para imprimir os dados da linha e sua respectiva distância
void imprime_linha(tipo_linha linha) {
    float dist = distancia(linha.p1, linha.p2);
    printf("Ponto 1: (%.2f, %.2f)\n", linha.p1.x, linha.p1.y);
    printf("Ponto 2: (%.2f, %.2f)\n", linha.p2.x, linha.p2.y);
    printf("Distancia: %.2f\n", dist);
}

int main() {
    tipo_ponto p1, p2;
    tipo_linha linha;
    FILE* arquivo = fopen("pontos.txt", "r");
    carrega_pontos(arquivo, &p1, &p2);
    fclose(arquivo);
    linha.p1 = p1;
    linha.p2 = p2;
    imprime_linha(linha);
    return 0;
}
