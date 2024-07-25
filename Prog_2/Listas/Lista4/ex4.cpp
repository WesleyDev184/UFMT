#include <iostream>
#include <string>

using namespace std;

class Carro
{
private:
  string marca;
  string modelo;
  int ano;
  int quilometragem;

public:
  Carro()
  {
    marca = "";
    modelo = "";
    ano = 0;
    quilometragem = 0;
  }
  Carro(string marca, string modelo, int ano, int quilometragem)
  {
    this->marca = marca;
    this->modelo = modelo;
    this->ano = ano;
    this->quilometragem = quilometragem;
  }
  void setMarca(string marca)
  {
    this->marca = marca;
  }
  void setModelo(string modelo)
  {
    this->modelo = modelo;
  }
  void setAno(int ano)
  {
    this->ano = ano;
  }
  void setQuilometragem(int quilometragem)
  {
    this->quilometragem = quilometragem;
  }
  string getMarca()
  {
    return marca;
  }
  string getModelo()
  {
    return modelo;
  }
  int getAno()
  {
    return ano;
  }
  int getQuilometragem()
  {
    return quilometragem;
  }
  void dirigir(int km)
  {
    quilometragem += km;
  }
  void mostrarDados()
  {
    cout << "Marca: " << marca << ", Modelo: " << modelo << ", Ano: " << ano << ", Quilometragem: " << quilometragem << endl;
  }
};

int main()
{
  Carro car1("Toyota", "Corolla", 2020, 15000);
  car1.mostrarDados(); // Marca : Toyota , Modelo : Corolla , Ano : 2020 ,Quilometragem:15000 
  car1.dirigir(500);
  car1.mostrarDados(); // Marca : Toyota , Modelo : Corolla , Ano : 2020 ,Quilometragem:15500
  return 0;
}