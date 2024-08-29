#ifndef ITEM_VESTUARIO_H
#define ITEM_VESTUARIO_H

#include "item.h"
#include <string>

using namespace std;

class ItemVestuario : public Item
{
public:
  ItemVestuario();
  ItemVestuario(int codigo, double preco, int qtdEstoque, const string &tamanho, const string &cor);

  void display() const override;
  void setTamanho(const string &tamanho);
  void setCor(const string &cor);
  string getTamanho() const;
  string getCor() const;

private:
  string tamanho;
  string cor;
};

#endif // ITEM_VESTUARIO_H
