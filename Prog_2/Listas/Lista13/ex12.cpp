#include <iostream>
#include <vector>

using namespace std;

template <typename Iterator>
bool iteradoresIguais(Iterator it1, Iterator it2)
{
  return it1 == it2;
}

int main()
{
  vector<int> numeros = {10, 20, 30, 40, 50};

  auto it1 = numeros.begin() + 2;
  auto it2 = numeros.begin() + 2;
  auto it3 = numeros.begin() + 1;

  if (iteradoresIguais(it1, it2))
  {
    cout << "it1 e it2 apontam para o mesmo elemento." << endl;
  }
  else
  {
    cout << "it1 e it2 não apontam para o mesmo elemento." << endl;
  }

  if (iteradoresIguais(it1, it3))
  {
    cout << "it1 e it3 apontam para o mesmo elemento." << endl;
  }
  else
  {
    cout << "it1 e it3 não apontam para o mesmo elemento." << endl;
  }

  return 0;
}
