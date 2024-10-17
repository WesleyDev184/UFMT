#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Pessoa
{
  string nome;
  int idade;
};

int main()
{
  ifstream arquivoEntrada("in.txt");
  ofstream arquivoSaida("resultados.txt");
  vector<Pessoa> pessoas;

  // Verifica se o arquivo de entrada foi aberto corretamente
  if (!arquivoEntrada)
  {
    cerr << "Erro ao abrir o arquivo de entrada!" << endl;
    return 1;
  }

  // Verifica se o arquivo de saída foi aberto corretamente
  if (!arquivoSaida)
  {
    cerr << "Erro ao abrir o arquivo de saída!" << endl;
    return 1;
  }

  Pessoa pessoa;
  // Lê o arquivo de entrada e armazena os dados no vetor de pessoas
  while (arquivoEntrada >> pessoa.nome >> pessoa.idade)
  {
    pessoas.push_back(pessoa);
  }

  cout << "Dados lidos com sucesso!" << endl;
  // Fecha o arquivo de entrada após a leitura
  arquivoEntrada.close();

  // Escreve os dados formatados no arquivo de saída
  for (const auto &p : pessoas)
  {
    arquivoSaida << "Nome: " << p.nome << ", Idade: " << p.idade << endl;
  }

  // Fecha o arquivo de saída após a escrita
  arquivoSaida.close();

  // Exibe mensagens de sucesso
  cout << "Dados gravados no arquivo formatado: resultados.txt" << endl;

  return 0;
}
