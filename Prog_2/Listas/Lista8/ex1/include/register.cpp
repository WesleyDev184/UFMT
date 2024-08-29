#include "register.h"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace Register
{
  Product::Product(int id, const string &name, double price, int quantity)
  {
    try
    {
      if (price < 0)
        throw invalid_argument("Preço não pode ser negativo.");
      if (quantity < 0)
        throw invalid_argument("Quantidade não pode ser negativa.");

      this->id = id;
      this->name = name;
      this->price = price;
      this->quantity = quantity;
    }
    catch (const invalid_argument &e)
    {
      cerr << "Erro ao criar produto: " << e.what() << endl;
      throw; // Re-lança a exceção para ser tratada em outro lugar, se necessário.
    }
  }

  void Product::display() const
  {
    try
    {
      cout << "Product: " << this->name << endl;
      cout << "ID: " << this->id << endl;
      cout << "Price: " << this->price << endl;
      cout << "Quantity: " << this->quantity << endl;
    }
    catch (const exception &e)
    {
      cerr << "Erro ao exibir produto: " << e.what() << endl;
    }
  }

  void Product::setPrice(double price)
  {
    try
    {
      if (price < 0)
        throw invalid_argument("Preço não pode ser negativo.");
      this->price = price;
    }
    catch (const invalid_argument &e)
    {
      cerr << "Erro ao definir o preço: " << e.what() << endl;
    }
  }

  void Product::setQuantity(int quantity)
  {
    try
    {
      if (quantity < 0)
        throw invalid_argument("Quantidade não pode ser negativa.");
      this->quantity = quantity;
    }
    catch (const invalid_argument &e)
    {
      cerr << "Erro ao definir a quantidade: " << e.what() << endl;
    }
  }

  int Product::getId() const
  {
    try
    {
      return this->id;
    }
    catch (const exception &e)
    {
      cerr << "Erro ao obter o ID: " << e.what() << endl;
      return -1; // Retorna um valor inválido em caso de erro.
    }
  }

  string Product::getName() const
  {
    try
    {
      return this->name;
    }
    catch (const exception &e)
    {
      cerr << "Erro ao obter o nome: " << e.what() << endl;
      return "";
    }
  }

  double Product::getPrice() const
  {
    try
    {
      return this->price;
    }
    catch (const exception &e)
    {
      cerr << "Erro ao obter o preço: " << e.what() << endl;
      return -1.0; // Retorna um valor inválido em caso de erro.
    }
  }

  int Product::getQuantity() const
  {
    try
    {
      return this->quantity;
    }
    catch (const exception &e)
    {
      cerr << "Erro ao obter a quantidade: " << e.what() << endl;
      return -1; // Retorna um valor inválido em caso de erro.
    }
  }
}
