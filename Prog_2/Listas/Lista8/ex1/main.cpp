#include <iostream>
#include <vector>
#include "include/register.h"
#include "include/search.h"

using namespace std;
using namespace Register;
using namespace SearchSpace;

int main()
{
  Product product1(1, "Product 1", 10.0, 5);
  Product product2(2, "Product 2", 20.0, 10);
  Product product3(3, "Product 3", 30.0, 15);

  Search search;
  search.addProduct(product1);
  search.addProduct(product2);
  search.addProduct(product3);


  cout << "busca do produto com ID 2:" << endl
       << endl;
  Product *product = search.findProduct(2);
  if (product != nullptr)
  {
    product->display();
    cout << endl;
  }

  cout << "Todos os produtos:" << endl
       << endl;
  vector<Product> products = search.getProducts();
  for (auto &product : products)
  {
    product.display();
    cout << endl;
  }

  search.removeProduct(2);

  cout << "Todos os produtos após a remoção do produto 2:" << endl
       << endl;

  products = search.getProducts();
  for (auto &product : products)
  {
    product.display();
    cout << endl;
  }

  return 0;
}