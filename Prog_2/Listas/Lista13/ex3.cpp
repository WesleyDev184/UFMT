#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
  map<string, int> frutas = {
      {"maca", 5},
      {"banana", 3},
      {"laranja", 8}};

  cout << "Quantidade inicial de frutas:" << endl;
  for (map<string, int>::iterator it = frutas.begin(); it != frutas.end(); ++it)
  {
    cout << it->first << ": " << it->second << endl;
  }

  for (map<string, int>::iterator it = frutas.begin(); it != frutas.end(); ++it)
  {
    it->second += 2;
  }

  cout << "\nQuantidade de frutas após atualização:" << endl;
  for (map<string, int>::iterator it = frutas.begin(); it != frutas.end(); ++it)
  {
    cout << it->first << ": " << it->second << endl;
  }

  return 0;
}
