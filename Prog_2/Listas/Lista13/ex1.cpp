#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> numeros = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  cout << "Valores iniciais do vetor: ";
  for (vector<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  for (vector<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    *it *= 2;
  }

  cout << "Valores do vetor após duplicação: ";
  for (vector<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}
