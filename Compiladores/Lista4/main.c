/**
 * @file main.c
 * @brief Funcao principal do compilador
 * @version 0.1
 * @date 2021-11-24
 *
 */

#include "main.h"

/**
 * @brief Funcao principal (main) do compilador
 *
 * @return int
 */
int main()
{

  int acept;
  acept = false;

  initLex();              // Carrega codigo
  lookahead = getToken(); // Inicializacao do lookahead

  acept = list(); // Chamada da derivacao/funcao inicial da gramatica

  // Verifica aceitacao da cadeia/codigo
  if (acept)
  {
    printf("\tCadeia PERTENCENTE a linguagem\n");
  }
  else
  {
    printf("\tCadeia NAO pertencente a linguagem\n");
  }

  return 1;
}