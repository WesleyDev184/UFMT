#include "vendas.h"
#include <iostream>

using namespace std;

void realizarVenda(Item *item, int quantidade)
{
  if (item->getQtdEstoque() < quantidade)
  {
    throw runtime_error("Quantidade em estoque insuficiente.");
  }
  else
  {
    // Atualiza a quantidade em estoque
    item->setQtdEstoque(item->getQtdEstoque() - quantidade);
    cout << "Venda realizada com sucesso!" << endl;
  }
}
