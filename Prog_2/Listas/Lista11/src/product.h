#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product
{
private:
  float price;
  string name;
  string category;

public:
  Product(float p, string n, string c);
  // Compares two products by their price
  bool operator<(const Product &p) const;
  bool operator>(const Product &p) const;
  // Compares two products by their name
  bool orderByName(const Product &p) const;
  // Compares two products by their category
  bool orderByCategory(const Product &p) const;

  void print() const;
};

#endif // PRODUCT_H