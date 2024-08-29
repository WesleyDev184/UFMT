#ifndef SEARCH_H
#define SEARCH_H

#include <map>
#include <vector>
#include <string>
#include "register.h"

using namespace std;
using namespace Register;

namespace SearchSpace
{
  class Search
  {
  public:
    Search(){};
    void addProduct(const Product &product);
    void removeProduct(int id);
    Product *findProduct(int id);
    vector<Product> getProducts() const;

  private:
    map<int, Product> products; // Usando map para associar ID ao produto
  };
}

#endif // SEARCH_H
