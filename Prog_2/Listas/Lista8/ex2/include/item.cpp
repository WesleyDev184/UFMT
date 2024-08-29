#include "Item.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Item::Item(int codigo, double preco, int qtdEstoque)
{
  try
  {
    if (preco < 0)
    {
      throw invalid_argument("Preço não pode ser negativo.");
    }
    if (qtdEstoque < 0)
    {
      throw invalid_argument("Quantidade em estoque não pode ser negativa.");
    }

    this->codigo = codigo;
    this->preco = preco;
    this->qtdEstoque = qtdEstoque;
  }
  catch (const exception &e)
  {
    cerr << e.what() << endl;
  }
}

void Item::display() const
{
  cout << "Código: " << codigo << endl;
  cout << "Preço: " << preco << endl;
  cout << "Quantidade em estoque: " << qtdEstoque << endl;
}

void Item::setPreco(double preco)
{
  try
  {
    if (preco < 0)
    {
      throw invalid_argument("Preço não pode ser negativo.");
    }
    this->preco = preco;
  }
  catch (const invalid_argument &e)
  {
    cerr << "Erro ao definir o preço: " << e.what() << endl;
  }
}

void Item::setQtdEstoque(int qtdEstoque)
{
  try
  {
    if (qtdEstoque < 0)
    {
      throw invalid_argument("Quantidade em estoque não pode ser negativa.");
    }
    this->qtdEstoque = qtdEstoque;
  }
  catch (const invalid_argument &e)
  {
    cerr << "Erro ao definir a quantidade em estoque: " << e.what() << endl;
  }
}

int Item::getCodigo() const
{
  return codigo;
}

double Item::getPreco() const
{
  return preco;
}

int Item::getQtdEstoque() const
{
  return qtdEstoque;
}

