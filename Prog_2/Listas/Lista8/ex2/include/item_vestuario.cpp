#include "item_vestuario.h"
#include <iostream>

using namespace std;

ItemVestuario::ItemVestuario() : Item(), tamanho("Não especificado"), cor("Não especificada") {}

ItemVestuario::ItemVestuario(int codigo, double preco, int qtdEstoque, const string &tamanho, const string &cor)
    : Item(codigo, preco, qtdEstoque)
{
  setTamanho(tamanho);
  setCor(cor);
}

void ItemVestuario::display() const
{
  cout << "Informações do item de vestuário:" << endl;
  Item::display(); // Chama o método display da classe base
  cout << "Tamanho: " << tamanho << endl;
  cout << "Cor: " << cor << endl;
  cout << endl;
}

void ItemVestuario::setTamanho(const string &tamanho)
{
  try
  {
    if (tamanho.empty())
    {
      throw invalid_argument("Tamanho não pode ser uma string vazia.");
    }
    this->tamanho = tamanho;
  }
  catch (const invalid_argument &e)
  {
    cerr << "Erro ao definir o tamanho: " << e.what() << endl;
  }
}

void ItemVestuario::setCor(const string &cor)
{
  try
  {
    if (cor.empty())
    {
      throw invalid_argument("Cor não pode ser uma string vazia.");
    }
    this->cor = cor;
  }
  catch (const invalid_argument &e)
  {
    cerr << "Erro ao definir a cor: " << e.what() << endl;
  }
}

string ItemVestuario::getTamanho() const
{
  return tamanho;
}

string ItemVestuario::getCor() const
{
  return cor;
}