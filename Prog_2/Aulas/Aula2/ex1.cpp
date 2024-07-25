#include <iostream>
#include <memory>

using namespace std;

int main()
{
  shared_ptr<int> sp1 = make_shared<int>(10); // Corrigido: Especificação de tipo <int>
  weak_ptr<int> wp = sp1;                     // Corrigido: Especificação de tipo <int>

  cout << wp.use_count() << endl; // use_count() retorna o número de shared_ptr que compartilham o objeto
  sp1.reset();                    // Reseta o shared_ptr, destruindo o objeto gerenciado se não houver outras referências
  cout << wp.use_count() << endl; // use_count() agora deve retornar 0

  return 0;
}
