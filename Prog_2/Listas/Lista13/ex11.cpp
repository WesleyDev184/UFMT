#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
  vector<int> numeros = {1, 2, 3, 4, 5};

  cout << "Vetor em ordem inversa: ";
  for (reverse_iterator<vector<int>::iterator> it = numeros.rbegin(); it != numeros.rend(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}
