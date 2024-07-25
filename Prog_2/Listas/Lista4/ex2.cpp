#include <iostream>
#include <string>

using namespace std;

class Livro
{
private:
  string titulo;
  string autor;
  int anoPublicacao;
  int numPaginas;

public:
  Livro()
  {
    titulo = "";
    autor = "";
    anoPublicacao = 0;
    numPaginas = 0;
  }

  Livro(string titulo, string autor, int anoPublicacao, int numPaginas)
  {
    this->titulo = titulo;
    this->autor = autor;
    this->anoPublicacao = anoPublicacao;
    this->numPaginas = numPaginas;
  }

  void setTitulo(string titulo)
  {
    this->titulo = titulo;
  }

  void setAutor(string autor)
  {
    this->autor = autor;
  }

  void setAnoPublicacao(int anoPublicacao)
  {
    this->anoPublicacao = anoPublicacao;
  }

  void setPaginas(int numPaginas)
  {
    this->numPaginas = numPaginas;
  }

  string getTitulo()
  {
    return titulo;
  }

  string getAutor()
  {
    return autor;
  }

  int getAnoPublicacao()
  {
    return anoPublicacao;
  }

  int getNumPaginas()
  {
    return numPaginas;
  }

  void mostrarDados()
  {
    cout << "Titulo: " << titulo << ", ";
    cout << "Autor: " << autor << ", ";
    cout << "Ano de Publicacao: " << anoPublicacao << ", ";
    cout << "Numero de Paginas: " << numPaginas << endl;
  }
};

int main()
{
  Livro l1(" 1984 ", " George Orwell ", 1949, 328);
  l1.mostrarDados(); // Titulo : 1984 , Autor : George Orwell , Ano : 1949 , Paginas:328
  Livro l2(" Fogo Morto ", " Graciliano Ramos ", 1933, 229);
  l2.mostrarDados(); // Titulo : Fogo Morto , Autor : Graciliano Ramos ,Ano:1933, Paginas : 229
  l2.setPaginas(299);
  l2.mostrarDados(); // Titulo : Fogo Morto , Autor : Graciliano Ramos ,Ano:1933,Paginas:99
  return 0;
}