#ifndef ITEM_ELETRONICO_H
#define ITEM_ELETRONICO_H

#include "item.h"
#include <string>

using namespace std;

class ItemEletronico : public Item
{
public:
  ItemEletronico();
  ItemEletronico(int codigo, double preco, int qtdEstoque, const string &marca, const string &modelo);

  void display() const override;
  void setMarca(const string &marca);
  void setModelo(const string &modelo);
  string getMarca() const;
  string getModelo() const;

private:
  string marca;
  string modelo;
};

#endif // ITEM_ELETRONICO_H
