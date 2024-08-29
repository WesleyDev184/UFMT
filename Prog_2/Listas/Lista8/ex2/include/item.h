#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
  Item() : codigo(0), preco(0.0), qtdEstoque(0) {}
  Item(int codigo, double preco, int qtdEstoque);
  virtual void display() const;
  void setPreco(double preco);
  void setQtdEstoque(int qtdEstoque);
  int getCodigo() const;
  double getPreco() const;
  int getQtdEstoque() const;

private:
  int codigo;
  double preco;
  int qtdEstoque;
};

#endif // ITEM_H
