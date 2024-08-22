#include <iostream>
#include <string>
#include "classes/Biblioteca.h"
#include "classes/Membro.h"
#include "classes/Livro.h"

using namespace std;

static string nomeArquivoMembros = "membros.txt";
static string nomeArquivoLivros = "livros.txt";

static string menu = "1 - Registrar livro\n2 - Registrar membro\n3 - Listar livros\n4 - Listar membros\n5 - Emprestar livro\n6 - Devolver livro\n7 - Sair\n";

int main()
{
  bool loop = true;
  Biblioteca biblioteca;

  biblioteca.carregarLivros(nomeArquivoLivros);
  biblioteca.carregarMembros(nomeArquivoMembros);
  while (loop)
  {
    cout << menu << endl;

    int opcao;
    cin >> opcao;
    cout << endl;

    switch (opcao)
    {
    case 1:
    {
      string ISBN, titulo;
      cout << "Digite o ISBN do livro: ";
      cin >> ISBN;
      cout << "Digite o título do livro: ";
      cin >> titulo;

      Livro livro(ISBN, titulo, true);
      biblioteca.registrarLivro(livro);
      break;
    }

    case 2:
    {
      string id, nome;
      cout << "Digite o ID do membro: ";
      cin >> id;
      cout << "Digite o nome do membro: ";
      cin >> nome;

      int ID = stoi(id);

      Membro membro(ID, nome);
      biblioteca.registrarMembro(membro);
      break;
    }

    case 3:
    {
      biblioteca.ListarLivros();
      break;
    }

    case 4:
    {
      biblioteca.ListarMembros();
      break;
    }

    case 5:
    {
      string idMembro, ISBN;
      cout << "Digite o ID do membro: ";
      cin >> idMembro;
      cout << "Digite o ISBN do livro: ";
      cin >> ISBN;

      int ID = stoi(idMembro);

      biblioteca.emprestarLivro(ID, ISBN);
      break;
    }

    case 6:
    {
      string idMembro, ISBN;
      cout << "Digite o ID do membro: ";
      cin >> idMembro;
      cout << "Digite o ISBN do livro: ";
      cin >> ISBN;

      int ID = stoi(idMembro);

      biblioteca.devolverLivro(ID, ISBN);
      break;
    }

    case 7:
    {
      biblioteca.gravarLivros(nomeArquivoLivros);
      biblioteca.gravarMembros(nomeArquivoMembros);
      loop = false;
      break;
    }

    default:
    {
      cout << "Opção inválida" << endl;
      break;
    }
    }
  }
}