#include <iostream>
#include "Membro.h"

using namespace std;

int Membro::getID()
{
  return this->ID;
}

string Membro::getNome()
{
  return this->nome;
}

void Membro::exibirDados()
{
  cout << "ID: " << this->ID << endl;
  cout << "Nome: " << this->nome << endl;
  cout << "Livros emprestados: " << endl;
  for (Livro livro : this->livrosEmprestados)
  {
    cout << "  " << livro.getTitulo() << endl;
  }
}

void Membro::emprestarLivro(Livro livro)
{
  this->livrosEmprestados.push_back(livro);
}

vector<Livro> Membro::getLivrosEmprestados()
{
  return this->livrosEmprestados;
}