#include <iostream>
#include <string>

using namespace std;

class Produto
{
public:
  string nome;
  double preco;
  int quantidade;

  Produto(const string &n = "", double p = 0.0, int q = 0)
      : nome(n), preco(p), quantidade(q) {}

  // Sobrecarga do operador de soma (+)
  Produto operator+(const Produto &outro) const
  {
    if (nome == outro.nome && preco == outro.preco)
    {
      return Produto(nome, preco, quantidade + outro.quantidade);
    }
    else
    {
      // Se não forem iguais, retorna o próprio objeto
      return *this;
    }
  }

  // Sobrecarga do operador de subtração (-)
  Produto operator-(const Produto &outro) const
  {
    if (nome == outro.nome && preco == outro.preco)
    {
      return Produto(nome, preco, quantidade - outro.quantidade);
    }
    else
    {
      // Se não forem iguais, retorna o próprio objeto
      return *this;
    }
  }

  // Sobrecarga do operador de saída (<<)
  friend ostream &operator<<(ostream &os, const Produto &produto)
  {
    os << "Produto: " << produto.nome << ", Preço: R$ " << produto.preco << ", Quantidade: " << produto.quantidade;
    return os;
  }

  // Sobrecarga do operador de entrada (>>)
  friend istream &operator>>(istream &is, Produto &produto)
  {
    cout << "Digite o nome, preço e quantidade do produto: ";
    is >> produto.nome >> produto.preco >> produto.quantidade;
    return is;
  }

  bool operator==(const Produto &outro) const
  {
    return nome == outro.nome && preco == outro.preco;
  }

  bool operator!=(const Produto &outro) const
  {
    return !(*this == outro);
  }
};

int main()
{
  Produto produto1, produto2;

  // Leitura dos produtos
  cin >> produto1 >> produto2;

  // Impressão dos produtos
  cout << "Produto 1: " << produto1 << endl;
  cout << "Produto 2: " << produto2 << endl;

  if (produto1 == produto2)
  {
    std::cout << "Os produtos são iguais!" << std::endl;
  }
  else
  {
    std::cout << "Os produtos são diferentes!" << std::endl;
  }

  // Soma das quantidades se os produtos forem iguais
  Produto soma = produto1 - produto2;
  cout << "A soma das quantidades dos produtos é: " << soma.quantidade << " unidades" << endl;

  return 0;
}
