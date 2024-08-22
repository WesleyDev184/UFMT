#include <iostream>
#include "Livro.h" // Include the header file for the Livro class

using namespace std;

string Livro::getISBN()
{
  return this->ISBN;
}

string Livro::getTitulo()
{
  return this->titulo;
}

bool Livro::isDisponivel()
{
  return this->disponivel;
}

void Livro::emprestar()
{
  if (this->disponivel)
  {
    this->disponivel = false;
    cout << "Livro emprestado com sucesso!" << endl;
  }
  else
  {
    cout << "Livro indisponível para empréstimo!" << endl;
  }
}

void Livro::devolver()
{
  if (!this->disponivel)
  {
    this->disponivel = true;
    cout << "Livro devolvido com sucesso!" << endl;
  }
  else
  {
    cout << "Livro já está disponível!" << endl;
  }
}

void Livro::exibirDados()
{
  cout << "ISBN: " << this->ISBN << endl;
  cout << "Título: " << this->titulo << endl;
  cout << "Disponível: " << (this->disponivel ? "Sim" : "Não") << endl;
}