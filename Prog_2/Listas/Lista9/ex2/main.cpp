// Crie um programa que gerencie o controle de qualidade de produtos em uma f´abrica, categorizando-os
// por tipo e n´ıvel de qualidade (por exemplo, Alto, M´edio, Baixo). Armazene a quantidade de produtos
// em uma matriz. Utilize enums tradicionais para representar os tipos de produtos e os n´ıveis de qualidade.
// Tarefa: O programa deve permitir que o usu´ario insira a quantidade de produtos em cada categoria
// e exiba o total de produtos de cada tipo que possuem alto n´ıvel de qualidade.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class TipoProduto
{
  Eletronico,
  Alimenticio,
  Vestuario,
  Limpeza
};

enum class NivelQualidade
{
  Alto,
  Medio,
  Baixo
};

struct Produto
{
  TipoProduto tipo;
  NivelQualidade qualidade;
};

int main()
{
  vector<Produto> produtos;
  int qtdProdutos;
  Produto produto;

  cout << "Digite a quantidade de produtos: ";
  cin >> qtdProdutos;

  for (int i = 0; i < qtdProdutos; i++)
  {
    int tipo, qualidade;
    cout << "Digite o tipo do produto (0 - Eletronico, 1 - Alimenticio, 2 - Vestuario, 3 - Limpeza): ";
    cin >> tipo;
    cout << "Digite o nivel de qualidade do produto (0 - Alto, 1 - Medio, 2 - Baixo): ";
    cin >> qualidade;

    produto.tipo = static_cast<TipoProduto>(tipo);
    produto.qualidade = static_cast<NivelQualidade>(qualidade);

    produtos.push_back(produto);
  }

  int totalProdutosAlto = 0;
  for (int i = 0; i < produtos.size(); i++)
  {
    if (produtos[i].qualidade == NivelQualidade::Alto)
    {
      totalProdutosAlto++;
    }
  }

  cout << "Total de produtos com alto nivel de qualidade: " << totalProdutosAlto << endl;

  return 0;
}