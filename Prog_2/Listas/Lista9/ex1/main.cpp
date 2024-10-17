#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

enum PlantType
{
  Cactos,
  Samambaias,
  Orquideas
};

int main()
{
  vector<float> umidade(3, 0);
  float umidadeCactos, umidadeSamambaias, umidadeOrquideas;

  cout << "Digite o nivel de umidade em % para Cactos: ";
  cin >> umidadeCactos;
  umidade[Cactos] = umidadeCactos;

  cout << "Digite o nivel de umidade em % para Samambaias: ";
  cin >> umidadeSamambaias;
  umidade[Samambaias] = umidadeSamambaias;

  cout << "Digite o nivel de umidade em % para Orquideas: ";
  cin >> umidadeOrquideas;
  umidade[Orquideas] = umidadeOrquideas;

  float media = (umidade[Cactos] + umidade[Samambaias] + umidade[Orquideas]) / 3;

  cout << fixed << setprecision(2);
  cout << "A media de umidade de todas as plantas monitoradas e: " << media << "%" << endl;

  return 0;
}