#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
  string texto = "abracadabra";

  unordered_map<char, int> contagem;

  for (char c : texto)
  {
    contagem[c]++;
  }

  cout << "Ocorrências de cada caractere:" << endl;
  for (auto it = contagem.begin(); it != contagem.end(); ++it)
  {
    cout << it->first << ": " << it->second << endl;
  }

  return 0;
}
