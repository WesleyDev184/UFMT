#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <vector>
#include <string>
#include "Membro.h"
#include "Livro.h"

class Biblioteca
{
private:
  vector<Membro> membros;
  vector<Livro> livros;

public:
  Biblioteca()
  {
    membros = {};
    livros = {};
  };
  void carregarLivros(string nomeArquivo);
  void carregarMembros(string nomeArquivo);
  void registrarMembro(Membro membro);
  void registrarLivro(Livro livro);
  void gravarLivros(string nomeArquivo);
  void gravarMembros(string nomeArquivo);
  void ListarMembros();
  void ListarLivros();
  void emprestarLivro(int idMembro, string ISBN);
  void devolverLivro(int idMembro, string ISBN);
};

#endif // BIBLIOTECA_H