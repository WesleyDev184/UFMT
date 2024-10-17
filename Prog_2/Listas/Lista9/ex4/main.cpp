#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Nutriente
{
  Calorias,
  Proteinas,
  Carboidratos
};

enum class Alimento
{
  Arroz,
  Feijao,
  Carne,
  Ovo,
  Macarrao,
  Invalido
};

int main()
{
  vector<vector<float>> informacoesNutricionais(5, vector<float>(3, 0));
  informacoesNutricionais[static_cast<int>(Alimento::Arroz)][static_cast<int>(Nutriente::Calorias)] = 130;
  informacoesNutricionais[static_cast<int>(Alimento::Arroz)][static_cast<int>(Nutriente::Proteinas)] = 2.5;
  informacoesNutricionais[static_cast<int>(Alimento::Arroz)][static_cast<int>(Nutriente::Carboidratos)] = 28.5;

  informacoesNutricionais[static_cast<int>(Alimento::Feijao)][static_cast<int>(Nutriente::Calorias)] = 100;
  informacoesNutricionais[static_cast<int>(Alimento::Feijao)][static_cast<int>(Nutriente::Proteinas)] = 6;
  informacoesNutricionais[static_cast<int>(Alimento::Feijao)][static_cast<int>(Nutriente::Carboidratos)] = 20;

  informacoesNutricionais[static_cast<int>(Alimento::Carne)][static_cast<int>(Nutriente::Calorias)] = 200;
  informacoesNutricionais[static_cast<int>(Alimento::Carne)][static_cast<int>(Nutriente::Proteinas)] = 20;
  informacoesNutricionais[static_cast<int>(Alimento::Carne)][static_cast<int>(Nutriente::Carboidratos)] = 0;

  informacoesNutricionais[static_cast<int>(Alimento::Ovo)][static_cast<int>(Nutriente::Calorias)] = 70;
  informacoesNutricionais[static_cast<int>(Alimento::Ovo)][static_cast<int>(Nutriente::Proteinas)] = 6;
  informacoesNutricionais[static_cast<int>(Alimento::Ovo)][static_cast<int>(Nutriente::Carboidratos)] = 0.5;

  informacoesNutricionais[static_cast<int>(Alimento::Macarrao)][static_cast<int>(Nutriente::Calorias)] = 200;
  informacoesNutricionais[static_cast<int>(Alimento::Macarrao)][static_cast<int>(Nutriente::Proteinas)] = 7;
  informacoesNutricionais[static_cast<int>(Alimento::Macarrao)][static_cast<int>(Nutriente::Carboidratos)] = 40;

  string alimento;
  bool continuar = true;

  while (continuar)
  {
    cout << "Digite o alimento que deseja consultar ('Sair' para sair): ";
    cin >> alimento;

    Alimento alimentoEnum;

    if (alimento == "Arroz")
      alimentoEnum = Alimento::Arroz;
    else if (alimento == "Feijao")
      alimentoEnum = Alimento::Feijao;
    else if (alimento == "Carne")
      alimentoEnum = Alimento::Carne;
    else if (alimento == "Ovo")
      alimentoEnum = Alimento::Ovo;
    else if (alimento == "Macarrao")
      alimentoEnum = Alimento::Macarrao;
    else if (alimento == "Sair")
    {
      continuar = false;
      continue;
    }
    else
    {
      cout << "Alimento não reconhecido." << endl;
      continue;
    }

    cout << "Calorias: " << informacoesNutricionais[static_cast<int>(alimentoEnum)][static_cast<int>(Nutriente::Calorias)] << endl;
    cout << "Proteinas: " << informacoesNutricionais[static_cast<int>(alimentoEnum)][static_cast<int>(Nutriente::Proteinas)] << endl;
    cout << "Carboidratos: " << informacoesNutricionais[static_cast<int>(alimentoEnum)][static_cast<int>(Nutriente::Carboidratos)] << endl;
  }

  cout << "Programa encerrado." << endl;

  return 0;
}
