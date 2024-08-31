#ifndef REGISTER_H
#define REGISTER_H

#include <string>

using namespace std;

namespace Register
{
  class Product
  {
  public:
    Product() : id(0), name(""), price(0.0), quantity(0) {}
    Product(int id, const string &name, double price, int quantity);
    void display() const;
    void setPrice(double price);
    void setQuantity(int quantity);
    int getId() const;
    string getName() const;
    double getPrice() const;
    int getQuantity() const;

  private:
    int id;
    string name;
    double price;
    int quantity;
  };
}

#endif // REGISTER_H
