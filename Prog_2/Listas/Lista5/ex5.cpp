#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Transporte
{
public:
  virtual void iniciar() const = 0;
  virtual void parar() const = 0;
  virtual ~Transporte() {}
};

class Carro : public Transporte
{
private:
  int kilometragem;

public:
  Carro(int km)
  {
    this->kilometragem = km;
  }

  Carro()
  {
    this->kilometragem = 0;
  };

  void setKilometragem(int km)
  {
    this->kilometragem = km;
  }

  int getKilometragem()
  {
    return this->kilometragem;
  }

  void iniciar() const override
  {
    cout << "Carro iniciado." << " Kilometragem: " << this->kilometragem << endl;
  }

  void parar() const override
  {
    cout << "Carro parado." << endl;
  }
};

class Bicicleta : public Transporte
{
public:
  void iniciar() const override
  {
    cout << "Bicicleta iniciada." << endl;
  }

  void parar() const override
  {
    cout << "Bicicleta parada." << endl;
  }
};

class Aviao : public Transporte
{
private:
  int horasVoo;
  int altitude;

public:
  Aviao(int horas, int alt)
      : horasVoo(horas), altitude(alt)
  {
  }

  void setHorasVoo(int horas)
  {
    horasVoo = horas;
  }

  void setAltitude(int alt)
  {
    altitude = alt;
  }

  void iniciar() const override
  {
    cout << "Avião iniciado. Horas de voo: " << horasVoo << " Altitude: " << altitude << " pés." << endl;
  }

  void parar() const override
  {
    cout << "Avião parado." << endl;
  }
};

int main()
{
  vector<shared_ptr<Transporte>> transportes;

  transportes.push_back(make_shared<Carro>(50000));
  transportes.push_back(make_shared<Bicicleta>());
  transportes.push_back(make_shared<Aviao>(100, 35000));

  for (const auto &transporte : transportes)
  {
    transporte->iniciar();
    transporte->parar();
    cout << endl;
  }

  return 0;
}
