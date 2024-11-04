#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
  queue<string> fila;

  fila.push("primeiro");
  fila.push("segundo");
  fila.push("terceiro");

  cout << "Removendo elementos da fila:" << endl;
  while (!fila.empty())
  {
    cout << "Frente: " << fila.front() << endl;
    fila.pop();
  }

  return 0;
}
