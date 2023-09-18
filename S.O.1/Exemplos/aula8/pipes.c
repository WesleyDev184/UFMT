#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{

  int id;
  int fd[2]; // descritores do pipe

  if (pipe(fd) == -1)
  {
    perror("erro ao criar o pipe");
    exit(EXIT_FAILURE);
  }

  id = fork();

  if (id == -1)
  {
    perror("erro ao gerar o fork");
    exit(EXIT_FAILURE);
  }

  if (id == 0)
  {
    // filho
    char buffer[100];                                  // buffer para armazenar a mensagem
    read(fd[0], buffer, sizeof(buffer));               // lê a mensagem do teclado
    printf("filho - recebi a mensagem: %s\n", buffer); // imprime a mensagem
    close(fd[0]);                                      // fecha o descritor de leitura
  }
  else
  {
    // pai
    const char *msg = "mensagem do pai"; // mensagem a ser enviada
    write(fd[1], msg, strlen(msg));      // escreve a mensagem no pipe
    close(fd[1]);                        // fecha o descritor de escrita
    wait(NULL);                          // espera o filho terminar
  }

  return 0;
}