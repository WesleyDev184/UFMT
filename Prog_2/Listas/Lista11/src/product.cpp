// executa uma hello world

#include "product.h"
#include <iostream>

Product::Product(float p, string n, string c)
{
  price = p;
  name = n;
  category = c;
}

bool Product::operator<(const Product &p) const
{
  return price < p.price;
}

bool Product::operator>(const Product &p) const
{
  return price > p.price;
}

bool Product::orderByName(const Product &p) const
{
  return name < p.name;
}

bool Product::orderByCategory(const Product &p) const
{
  return category < p.category;
}

void Product::print() const
{
  cout << "Nome: " << name << endl;
  cout << "Categoria: " << category << endl;
  cout << "Preço: " << price << endl;
  cout << endl;
}