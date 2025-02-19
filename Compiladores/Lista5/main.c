/**
 * @file main.c
 * @brief Funcao principal do compilador
 * @version 0.1
 * @date 2021-11-24
 *
 */

#include "main.h"

extern type_token *lookahead;

/**
 * @brief Funcao principal (main) do compilador
 * 
 * @return int 
 */
int main(int argc, char *argv[]) {

  //Verifica a passagem de parametro
  if (argc != 2) {
      printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
      exit(EXIT_FAILURE);
  }
  int acept;
  acept = false;
  
  initLex(argv[1]); //Carrega codigo
  lookahead = getToken(); //Inicializacao do lookahead

  acept = E(); //Chamada da derivacao/funcao inicial da gramatica

  //Verifica aceitacao da cadeia/codigo
  if (acept) {
      printf("\tCadeia PERTENCENTE a linguagem\n");
  } else {
      printf("\tCadeia NAO pertencente a linguagem\n");
  }

  return 1;
}