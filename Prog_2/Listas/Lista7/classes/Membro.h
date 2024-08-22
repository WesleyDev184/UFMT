#ifndef MEMBRO_H
#define MEMBRO_H

#include <string>
#include <vector>
#include "Livro.h"

using namespace std;

class Membro
{
private:
  int ID;
  string nome;
  vector<Livro> livrosEmprestados;

public:
  Membro(int ID, string nome) : ID(ID), nome(nome) {};
  int getID();
  string getNome();
  void exibirDados();
  void emprestarLivro(Livro livro);
  vector<Livro> getLivrosEmprestados();
};

#endif // MEMBRO_H