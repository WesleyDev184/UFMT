#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de aluno
typedef struct aluno
{
  int matricula;
  float cr;
} TAluno;

typedef TAluno *Hash; // Hash é um vetor de ponteiros para TAluno

// Função para inicializar a tabela hash com NULL
void inicializa(Hash *tab, int m)
{
  int i;
  for (i = 0; i < m; i++)
  {
    tab[i] = NULL;
  }
}

// Função para alocar um novo aluno
TAluno *aloca(int mat, float cr)
{
  TAluno *novo = (TAluno *)malloc(sizeof(TAluno));
  novo->matricula = mat;
  novo->cr = cr;
  return novo;
}

// Função de hash usando o método da dobra
int hash(int mat, int m)
{
  int soma = 0;
  for (; mat > 0; mat /= 100)
  {
    soma += mat % 100; // Soma de dois dígitos
  }
  return soma % m; // Retorna o índice calculado
}

// Função para liberar a memória alocada para a tabela hash
void libera(Hash *tab, int m)
{
  int i;
  for (i = 0; i < m; i++)
  {
    if (tab[i])
    {
      free(tab[i]);
    }
  }
}

// Função para buscar um aluno na tabela hash
int busca(Hash *tab, int m, int mat)
{
  int pos = hash(mat, m); // Calcula o índice usando a função de hash
  if (tab[pos] != NULL)
  {
    TAluno *resp = tab[pos];
    if (resp->matricula == mat)
    {
      return pos; // Retorna o índice se o aluno for encontrado
    }
  }
  return -1; // Retorna -1 se o aluno não for encontrado
}

// Função para inserir um aluno na tabela hash
void insere(Hash *tab, int m, int mat, float cr)
{
  int ini = hash(mat, m); // Calcula o índice usando a função de hash
  if (tab[ini] == NULL)
  {
    tab[ini] = aloca(mat, cr); // Insere o aluno se a posição estiver vazia
  }
  else
  {
    printf("Compartimento ja ocupado -- insercao nao realizada\n");
  }
}

// Função para imprimir os elementos da tabela hash
void imprime(Hash *tab, int m)
{
  int h;
  for (int i = 0; i < m; i++)
  {
    h = i;
    printf("%d:\n", h);

    if (tab[h] != NULL)
    {
      TAluno *p = tab[h];
      printf("\tmat: %d\tcr: %f:\n", p->matricula, p->cr);
    }
  }
}

int main()
{
  int n = 5; // Número fixo de alunos
  int m = 7; // Tamanho da tabela hash

  Hash *tab[m];       // Declara um vetor de ponteiros para TAluno
  inicializa(tab, m); // Inicializa a tabela hash com NULL

  // Inserções fixas para testar o programa
  insere(tab, m, 12345, 8.5);
  insere(tab, m, 67890, 7.2);
  insere(tab, m, 54321, 9.0);
  insere(tab, m, 98765, 6.8);
  insere(tab, m, 11111, 5.5);

  imprime(tab, m); // Imprime os elementos da tabela hash

  char resp;

  do
  {
    int mat;
    printf("\nDigite a matrícula do aluno a ser buscado: ");
    scanf("%d", &mat); // Lê a matrícula para busca

    int ind = busca(tab, m, mat); // Procura o aluno na tabela
    if (ind == -1)
      printf("Elemento não encontrado!\n");
    else
    {
      TAluno *p = tab[ind];
      printf("Aluno encontrado:\n");
      printf("Matrícula: %d\tCR: %f\n", p->matricula, p->cr); // Imprime o aluno encontrado
    }
    printf("Deseja buscar outro aluno? (N/n para sair): ");
    scanf(" %c", &resp);
  } while ((resp != 'N') && (resp != 'n'));

  printf("\nTabela Hash:\n");
  imprime(tab, m); // Imprime os elementos da tabela hash

  libera(tab, m); // Libera a memória alocada

  return 0;
}
