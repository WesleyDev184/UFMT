#include "./src/product.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  vector<Product> products;
  products.push_back(Product(10, "Arroz", "Alimento"));
  products.push_back(Product(5, "Feijão", "Alimento"));
  products.push_back(Product(15, "Macarrão", "Alimento"));
  products.push_back(Product(20, "Sabão", "Limpeza"));
  products.push_back(Product(25, "Detergente", "Limpeza"));

  // menu de opções
  int option;
  do
  {
    cout << "1 - Adicionar produto" << endl;
    cout << "2 - Ordenar por preço" << endl;
    cout << "3 - Ordenar por nome" << endl;
    cout << "4 - Ordenar por categoria" << endl;
    cout << "0 - Sair" << endl;
    cout << "Escolha uma opção: ";
    cin >> option;

    if (option == 2 || option == 3 || option == 4)
    {
      int order;
      cout << "Escolha a ordem: " << endl;
      cout << "1 - Crescente" << endl;
      cout << "2 - Decrescente" << endl;
      cin >> order;

      bool ascending = (order == 1);

      switch (option)
      {
      case 2: // Ordenar por preço
      {
        if (ascending)
        {
          sort(products.begin(), products.end(), less<Product>());
        }
        else
        {
          sort(products.begin(), products.end(), greater<Product>());
        }
        break;
      }
      case 3: // Ordenar por nome
      {
        if (ascending)
        {
          sort(products.begin(), products.end(), [](Product a, Product b)
               { return a.orderByName(b); });
        }
        else
        {
          sort(products.begin(), products.end(), [](Product a, Product b)
               { return !a.orderByName(b); });
        }
        break;
      }
      case 4: // Ordenar por categoria
      {
        if (ascending)
        {
          sort(products.begin(), products.end(), [](Product a, Product b)
               { return a.orderByCategory(b); });
        }
        else
        {
          sort(products.begin(), products.end(), [](Product a, Product b)
               { return !a.orderByCategory(b); });
        }
        break;
      }
      }

      for (Product p : products)
      {
        p.print();
      }
    }
    else if (option == 1)
    {
      float price;
      string name, category;
      cout << "Digite o nome do produto: ";
      cin >> name;
      cout << "Digite a categoria do produto: ";
      cin >> category;
      cout << "Digite o preço do produto: ";
      cin >> price;
      Product p(price, name, category);
      products.push_back(p);
    }
    else if (option == 0)
    {
      cout << "Saindo..." << endl;
    }
    else
    {
      cout << "Opção inválida" << endl;
    }

  } while (option != 0);

  return 0;
}
