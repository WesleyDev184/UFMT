#include <iostream>
#include <vector>
#include <algorithm>
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

void Membro::removerLivro(string ISBN)
{
  for (int i = 0; i < this->livrosEmprestados.size(); i++)
  {
    if (this->livrosEmprestados[i].getISBN() == ISBN)
    {
      this->livrosEmprestados.erase(
          remove_if(this->livrosEmprestados.begin(), this->livrosEmprestados.end(), [ISBN](Livro &item)
                    { return item.getISBN() == ISBN; }),
          this->livrosEmprestados.end());
      ;
    }
  }
}

vector<Livro> Membro::getLivrosEmprestados()
{
  return this->livrosEmprestados;
}