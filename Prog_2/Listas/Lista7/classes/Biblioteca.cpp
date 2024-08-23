#include <iostream>
#include <fstream>
#include "Biblioteca.h"
#include "Livro.h"
#include "Membro.h"
#include <sys/stat.h>
#include <sstream>

using namespace std;

void Biblioteca::carregarLivros(string nomeArquivo)
{
  ifstream arquivo(nomeArquivo);

  if (!arquivo.is_open())
  {
    cerr << "Erro ao abrir o arquivo!" << endl;
    return;
  }

  string linha;
  while (getline(arquivo, linha))
  {
    stringstream ss(linha);
    string temp;
    string ISBN;
    string titulo;
    bool disponivel;

    // Extrair o ISBN
    getline(ss, ISBN, ';');

    // Extrair o título
    getline(ss, titulo, ';');

    // Extrair a disponibilidade
    getline(ss, temp, ';');
    disponivel = (temp == "true");

    this->livros.push_back(Livro(ISBN, titulo, disponivel));
  }

  arquivo.close();
}

void Biblioteca::carregarMembros(string nomeArquivo)
{
  ifstream arquivo(nomeArquivo);

  if (!arquivo.is_open())
  {
    cerr << "Erro ao abrir o arquivo!" << endl;
    return;
  }

  string linha;
  while (getline(arquivo, linha))
  {
    stringstream ss(linha);
    string temp;
    int id;
    string nome;
    vector<string> isbns;

    // Extrair o ID
    getline(ss, temp, ';');
    id = stoi(temp);

    // Extrair o nome
    getline(ss, nome, ';');

    // Extrair os ISBNs e armazenar no vector
    while (getline(ss, temp, ';'))
    {
      isbns.push_back(temp);
    }

    this->membros.push_back(Membro(id, nome));

    // Emprestar os livros ao membro
    for (int i = 0; i < isbns.size(); i++)
    {
      for (int j = 0; j < this->livros.size(); j++)
      {
        if (this->livros[j].getISBN() == isbns[i])
        {
          this->membros[this->membros.size() - 1].emprestarLivro(this->livros[j]);
        }
      }
    }
  }

  arquivo.close();
}

void Biblioteca::gravarMembros(string nomeArquivo)
{
  ofstream arquivo(nomeArquivo);

  if (!arquivo.is_open())
  {
    cerr << "Erro ao abrir o arquivo!" << endl;
    return;
  }

  for (auto &membro : this->membros)
  {
    arquivo << membro.getID() << ';' << membro.getNome();

    for (auto &livros : membro.getLivrosEmprestados())
    {
      arquivo << ';' << livros.getISBN();
    }

    arquivo << '\n';
  }

  arquivo.close();
}

void Biblioteca::gravarLivros(string nomeArquivo)
{
  ofstream arquivo(nomeArquivo, ios::trunc); // 'ios::trunc' limpa o conteúdo existente
  if (arquivo.is_open())
  {
    for (int i = 0; i < this->livros.size(); i++)
    {
      // Construir a linha no formato: ISBN;titulo;disponivel
      arquivo << this->livros[i].getISBN() << ";"
              << this->livros[i].getTitulo() << ";"
              << (this->livros[i].isDisponivel() ? "true" : "false") << "\n";
    }

    arquivo.close();
  }
  else
  {
    cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
  }
}

void Biblioteca::registrarMembro(Membro membro)
{
  this->membros.push_back(membro);
}

void Biblioteca::registrarLivro(Livro livro)
{
  this->livros.push_back(livro);
}

void Biblioteca::ListarMembros()
{
  if (this->membros.size() == 0)
  {
    cerr << "Nenhum membro cadastrado." << endl;
    return;
  }

  for (int i = 0; i < this->membros.size(); i++)
  {
    this->membros[i].exibirDados();
    cout << endl;
  }
}

void Biblioteca::ListarLivros()
{
  if (this->livros.size() == 0)
  {
    cerr << "Nenhum livro cadastrado." << endl;
    return;
  }

  for (int i = 0; i < this->livros.size(); i++)
  {
    this->livros[i].exibirDados();
    cout << endl;
  }
}

void Biblioteca::emprestarLivro(int idMembro, string ISBN)
{
  for (int i = 0; i < this->membros.size(); i++)
  {
    if (this->membros[i].getID() == idMembro)
    {
      for (int j = 0; j < this->livros.size(); j++)
      {
        if (this->livros[j].getISBN() == ISBN)
        {
          if (this->livros[j].isDisponivel())
          {
            this->membros[i].emprestarLivro(this->livros[j]);
            this->livros[j].emprestar();
          }
          else
          {
            cerr << "Livro não disponível para empréstimo." << endl;
          }
        }
      }
    }
  }
}

void Biblioteca::devolverLivro(int idMembro, string ISBN)
{
  for (int i = 0; i < this->membros.size(); i++)
  {
    if (this->membros[i].getID() == idMembro)
    {
      for (int j = 0; j < this->livros.size(); j++)
      {
        if (this->livros[j].getISBN() == ISBN)
        {
          this->livros[j].devolver();
          this->membros[i].removerLivro(ISBN);
        }
      }
    }
  }
}