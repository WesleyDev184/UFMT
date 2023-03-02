#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Define o tamanho máximo da pilha

// Define a estrutura da pilha
struct stack {
  int items[MAX_SIZE]; // Array de inteiros que armazena os elementos da pilha
  int top; // Variável que indica o índice do topo da pilha
};

// Função para inicializar a pilha, definindo o topo como -1 (pilha vazia)
void init_stack(struct stack *s) {
  s->top = -1;
}

// Função que verifica se a pilha está vazia, retornando 1 se sim e 0 caso contrário
int is_empty(struct stack *s) {
  return s->top == -1;
}

// Função que verifica se a pilha está cheia, retornando 1 se sim e 0 caso contrário
int is_full(struct stack *s) {
  return s->top == MAX_SIZE - 1;
}

// Função que adiciona um elemento ao topo da pilha
void push(struct stack *s, int item) {
  // Verifica se a pilha está cheia
  if (is_full(s)) {
    printf("Stack Overflow!\n"); // Se estiver cheia, exibe mensagem de erro
    return;
  }
  s->items[++s->top] = item; // Se não estiver cheia, adiciona o elemento e atualiza o topo
}

// Função que remove o elemento do topo da pilha e o retorna
int pop(struct stack *s) {
  // Verifica se a pilha está vazia
  if (is_empty(s)) {
    printf("Stack Underflow!\n"); // Se estiver vazia, exibe mensagem de erro
    return -1;
  }
  return s->items[s->top--]; // Se não estiver vazia, remove e retorna o elemento do topo, atualizando o topo
}

// Função principal
int main() {
  struct stack s; // Declara a pilha como uma variável do tipo struct stack
  init_stack(&s); // Inicializa a pilha usando a função init_stack e passando o endereço de memória da variável s

  int choice, item; // Declara as variáveis para armazenar a escolha do usuário e o item a ser adicionado/removido da pilha

  do {
    // Exibe o menu para o usuário
    printf("\n1. Push\n");
    printf("2. Pop\n");
    printf("3. Quit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice); // Lê a escolha do usuário

    switch (choice) {
      case 1: // Se escolher 1, adiciona um item à pilha
        printf("Enter the item to push: ");
        scanf("%d", &item);
        push(&s, item);
        break;

      case 2: // Se escolher 2, remove o item do topo da pilha
        printf("%d popped from stack\n", pop(&s));
        break;

      case 3: // Se escolher 3, encerra o programa
        printf("Exiting...\n");
        break;

      default: // Se escolher qualquer outra opção inválida, exibe mensagem de erro
        printf("Invalid choice!\n");
        break;
    }
  } while (choice != 3); // Repete o loop
