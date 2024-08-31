#include "include/vendas.h"
#include "include/item.h"
#include "include/item_eletronico.h"
#include "include/item_vestuario.h"
#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

int main()
{
  try
  {
    // Criando objetos com ponteiros inteligentes sem std::make_unique
    unique_ptr<ItemEletronico> laptop(new ItemEletronico(101, 2500.0, 10, "Dell", "XPS 15"));
    unique_ptr<ItemVestuario> camisa(new ItemVestuario(202, 100.0, 5, "M", "Azul"));

    laptop->display();
    camisa->display();

    // Testando o dynamic_cast
    Item *item = laptop.get();
    ItemEletronico *eletronicoPtr = dynamic_cast<ItemEletronico *>(item);
    if (eletronicoPtr)
    {
      cout << "Conversão bem-sucedida para Eletronico!" << endl;
    }
    else
    {
      cerr << "Falha na conversão para Eletronico." << endl;
    }

    // Tentando realizar uma venda
    realizarVenda(laptop.get(), 3);  // Sucesso
    realizarVenda(camisa.get(), 10); // Falha (exceção lançada)
  }
  catch (const bad_cast &e)
  {
    cerr << "Erro de cast: " << e.what() << endl;
  }
  catch (const runtime_error &e)
  {
    cerr << "Erro de runtime: " << e.what() << endl;
  }
  catch (const invalid_argument &e)
  {
    cerr << "Erro de argumento inválido: " << e.what() << endl;
  }

  return 0;
}
