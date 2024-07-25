#include <iostream>
#include <string>

using namespace std;

class Lampada
{
private:
  bool ligada;
  int watts;
  string tipo;
  string cor;
  string marca;

public:
  Lampada()
  {
    this->ligada = false;
    this->watts = 0;
    this->tipo = "";
    this->cor = "";
    this->marca = "";
  };

  Lampada(bool ligada, int watts, string tipo, string cor, string marca)
  {
    this->ligada = ligada;
    this->watts = watts;
    this->tipo = tipo;
    this->cor = cor;
    this->marca = marca;
  }

  // setters
  void setLigada(bool ligada)
  {
    this->ligada = ligada;
  }

  void setWatts(int watts)
  {
    this->watts = watts;
  }

  void setTipo(string tipo)
  {
    this->tipo = tipo;
  }

  void setCor(string cor)
  {
    this->cor = cor;
  }

  void setMarca(string marca)
  {
    this->marca = marca;
  }

  // getters

  bool getLigada()
  {
    return this->ligada;
  }

  int getWatts()
  {
    return this->watts;
  }

  string getTipo()
  {
    return this->tipo;
  }

  string getCor()
  {
    return this->cor;
  }

  string getMarca()
  {
    return this->marca;
  }

  void status()
  {
    cout << "Ligada: " << this->ligada << endl;
    cout << "Watts: " << this->watts << endl;
    cout << "Tipo: " << this->tipo << endl;
    cout << "Cor: " << this->cor << endl;
    cout << "Marca: " << this->marca << endl;
  }
};

int main()
{
  Lampada lampada1(false, 100, "Incandescente", "Amarela", "Osram");
  Lampada lampada2(true, 60, "LED", "Branca", "Philips");

  lampada1.status();
  cout << endl;
  lampada2.status();

  return 0;
}