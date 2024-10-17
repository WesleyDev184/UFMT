#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm> // Para usar as funções min_element e max_element

using namespace std;

enum class Horario
{
  Manha,
  Tarde,
  Noite
};

int main()
{
  vector<float> temperaturas(3, 0);
  float temperaturaManha, temperaturaTarde, temperaturaNoite;

  cout << "Digite a temperatura em graus Celsius para a Manha: ";
  cin >> temperaturaManha;
  temperaturas[static_cast<int>(Horario::Manha)] = temperaturaManha;
  cout << "Digite a temperatura em graus Celsius para a Tarde: ";
  cin >> temperaturaTarde;
  temperaturas[static_cast<int>(Horario::Tarde)] = temperaturaTarde;
  cout << "Digite a temperatura em graus Celsius para a Noite: ";
  cin >> temperaturaNoite;
  temperaturas[static_cast<int>(Horario::Noite)] = temperaturaNoite;

  // Encontrar a temperatura máxima e mínima no vetor
  float tempMax = *max_element(temperaturas.begin(), temperaturas.end());
  float tempMin = *min_element(temperaturas.begin(), temperaturas.end());

  // Calcular a variação de temperatura
  float variacao = tempMax - tempMin;

  cout << fixed << setprecision(2);
  cout << "A variacao de temperatura ao longo do dia e: " << variacao << " graus Celsius" << endl;

  return 0;
}
