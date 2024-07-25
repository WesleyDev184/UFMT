#include <iostream>
#include <string>

using namespace std;

class Produto
{
private:
  string nome;
  float preco;
  int quantidade;

public:
  Produto()
  {
    nome = "";
    preco = 0;
    quantidade = 0;
  }

  Produto(string nome, float preco, int quantidade)
  {
    this->nome = nome;
    this->preco = preco;
    this->quantidade = quantidade;
  }

  void setNome(string nome)
  {
    this->nome = nome;
  }

  void setPreco(float preco)
  {
    this->preco = preco;
  }

  void setQuantidade(int quantidade)
  {
    this->quantidade = quantidade;
  }

  string getNome()
  {
    return nome;
  }

  float getPreco()
  {
    return preco;
  }

  int getQuantidade()
  {
    return quantidade;
  }

  void adicionarEstoque(int quantidade)
  {
    this->quantidade += quantidade;
  }

  void removerEstoque(int quantidade)
  {
    this->quantidade -= quantidade;
  }

  void mostrarDados()
  {
    cout << "Nome: " << nome << ", ";
    cout << "Preço: " << preco << ", ";
    cout << "Quantidade: " << quantidade << endl;
  }
};

int main()
{
  Produto p1("Notbook", 2500.0, 10);
  p1.mostrarDados();
  cout << endl;
  p1.adicionarEstoque(6);
  p1.mostrarDados();
  cout << endl;
  p1.removerEstoque(3);
  p1.mostrarDados();

  return 0;
}