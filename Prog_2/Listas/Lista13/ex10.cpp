#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> numeros = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto it = numeros.begin() + 2;
  cout << "Terceiro elemento antes da modificação: " << *it << endl;

  *it = 99;

  cout << "Vetor após a modificação: ";
  for (const auto &valor : numeros)
  {
    cout << valor << " ";
  }
  cout << endl;

  return 0;
}
