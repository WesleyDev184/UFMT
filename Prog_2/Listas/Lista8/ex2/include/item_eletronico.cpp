#include "item_eletronico.h"
#include <iostream>

using namespace std;

ItemEletronico::ItemEletronico() : Item(), marca("Desconhecida"), modelo("Desconhecido") {}

ItemEletronico::ItemEletronico(int codigo, double preco, int qtdEstoque, const string &marca, const string &modelo)
    : Item(codigo, preco, qtdEstoque), marca(marca), modelo(modelo) {}

void ItemEletronico::display() const
{
  cout << "Informações do item eletrônico:" << endl;
  Item::display(); // Chama o método display da classe base
  cout << "Marca: " << marca << endl;
  cout << "Modelo: " << modelo << endl;
  cout << endl;
}

void ItemEletronico::setMarca(const string &marca)
{
  this->marca = marca;
}

void ItemEletronico::setModelo(const string &modelo)
{
  this->modelo = modelo;
}

string ItemEletronico::getMarca() const
{
  return marca;
}

string ItemEletronico::getModelo() const
{
  return modelo;
}
