#include <iostream>
#include <stack>

using namespace std;

int main()
{
  stack<int> pilha;

  pilha.push(5);
  pilha.push(10);
  pilha.push(15);
  pilha.push(20);

  cout << "Removendo elementos da pilha:" << endl;
  while (!pilha.empty())
  {
    cout << "Topo: " << pilha.top() << endl;
    pilha.pop();
  }

  return 0;
}
