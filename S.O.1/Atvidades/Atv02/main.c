#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid_compile, pid_hello;
  int status;

  printf("Processo pai (%d) iniciado!\n", getpid());

  // Criação do primeiro filho para executar o GCC
  pid_compile = fork();

  if (pid_compile == 0)
  {
    // Código do processo filho para executar o GCC
    printf("Processo filho GCC (%d) iniciado!\n", getpid());
    execlp("gcc", "gcc", "olaMundo.c", "-o", "program", NULL);
    perror("Erro ao executar o GCC");
    exit(EXIT_FAILURE);
  }
  else if (pid_compile < 0)
  {
    perror("Erro ao criar o processo filho (GCC)");
    exit(EXIT_FAILURE);
  }

  // Espera pelo término do processo filho GCC
  wait(&status);
  if (WIFEXITED(status))
  {
    if (WEXITSTATUS(status) == EXIT_SUCCESS)
    {
      printf("Processo filho GCC (%d) terminou com sucesso!\n", pid_compile);
    }
    else
    {
      printf("Processo filho GCC (%d) terminou com erro!\n", pid_compile);
      exit(0);
    }
  }

  // Criação do segundo filho para executar "Olá Mundo!"
  pid_hello = fork();

  if (pid_hello == 0)
  {
    // Código do processo filho para imprimir "Olá Mundo!"
    printf("Processo filho Olá Mundo (%d) iniciado!\n", getpid());
    execl("./program", "program", NULL);
    exit(EXIT_SUCCESS);
  }
  else if (pid_hello < 0)
  {
    perror("Erro ao criar o processo filho (Olá Mundo)");
    exit(EXIT_FAILURE);
  }

  // Espera pelo término do processo filho "Olá Mundo!"
  wait(&status);
  if (WIFEXITED(status))
  {
    if (WEXITSTATUS(status) == EXIT_SUCCESS)
    {
      printf("Processo filho Olá Mundo (%d) terminou com sucesso!\n", pid_hello);
    }
    else
    {
      printf("Processo filho Olá Mundo (%d) terminou com erro!\n", pid_hello);
      exit(0);
    }
  }

  printf("Processo pai (%d) terminou!\n", getpid());

  return 0;
}
