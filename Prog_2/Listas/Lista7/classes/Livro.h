#ifndef LIVRO_H
#define LIVRO_H

#include <string>

using namespace std;

class Livro
{
private:
  string ISBN;
  string titulo;
  bool disponivel;

public:
  Livro(string ISBN, string titulo, bool dis) : ISBN(ISBN), titulo(titulo), disponivel(dis) {};
  string getISBN();
  string getTitulo();
  bool isDisponivel();
  void emprestar();
  void devolver();
  void exibirDados();
};

#endif // LIVRO_H