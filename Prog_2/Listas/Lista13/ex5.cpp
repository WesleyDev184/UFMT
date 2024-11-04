#include <iostream>
#include <deque>

using namespace std;

int main()
{
  deque<int> numeros;

  numeros.push_front(3);
  numeros.push_front(2);
  numeros.push_front(1);

  numeros.push_back(10);
  numeros.push_back(20);
  numeros.push_back(30);

  cout << "Elementos do deque: ";
  for (deque<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  numeros.pop_front();
  numeros.pop_back();

  cout << "Elementos do deque após remoção do primeiro e último: ";
  for (deque<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}
