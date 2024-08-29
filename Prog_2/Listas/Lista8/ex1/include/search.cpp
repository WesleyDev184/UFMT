#include "search.h"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace SearchSpace
{

  void Search::addProduct(const Product &product)
  {
    try
    {
      // verifica se o produto já existe
      if (this->products.find(product.getId()) != this->products.end())
      {
        throw invalid_argument("Produto com ID " + to_string(product.getId()) + " já existe.");
      }
      this->products[product.getId()] = product;
    }
    catch (const exception &e)
    {
      cerr << "Erro ao adicionar produto: " << e.what() << endl;
    }
  }

  void Search::removeProduct(int id)
  {
    try
    {
      if (this->products.erase(id) == 0)
      {
        throw runtime_error("Produto com ID " + to_string(id) + " não encontrado.");
      }
    }
    catch (const exception &e)
    {
      cerr << "Erro ao remover produto: " << e.what() << endl;
    }
  }

  Product *Search::findProduct(int id)
  {
    try
    {
      auto it = this->products.find(id);
      if (it != this->products.end())
      {
        return &it->second;
      }
      throw out_of_range("Produto com ID " + to_string(id) + " não encontrado.");
    }
    catch (const exception &e)
    {
      cerr << "Erro ao procurar produto: " << e.what() << endl;
      return nullptr;
    }
  }

  vector<Product> Search::getProducts() const
  {
    try
    {
      vector<Product> products;
      for (const auto &product : this->products)
      {
        products.push_back(product.second);
      }
      return products;
    }
    catch (const exception &e)
    {
      cerr << "Erro ao obter a lista de produtos: " << e.what() << endl;
      return {};
    }
  }
}
