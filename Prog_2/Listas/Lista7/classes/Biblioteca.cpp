#include <iostream>
#include <fstream>
#include "Biblioteca.h"
#include "Livro.h"
#include "Membro.h"
#include <sys/stat.h>

using namespace std;

bool arquivoExiste(const string &nomeArquivo)
{
  struct stat buffer;
  return (stat(nomeArquivo.c_str(), &buffer) == 0);
}

void Biblioteca::carregarLivros(string nomeArquivo)
{
  if (!arquivoExiste(nomeArquivo))
  {
    cerr << "Arquivo " << nomeArquivo << " não encontrado." << endl;
    return;
  }

  ifstream arquivo(nomeArquivo);
  string linha;
  while (getline(arquivo, linha))
  {
    // formato da linha: ISBN;titulo;disponivel
    string ISBN = linha.substr(0, linha.find(';'));
    linha = linha.substr(linha.find(';') + 1);
    string titulo = linha.substr(0, linha.find(';'));
    linha = linha.substr(linha.find(';') + 1);
    bool disponivel = linha == "true" ? true : false;

    Livro livro(ISBN, titulo, disponivel);
    this->livros.push_back(livro);
  }
}

void Biblioteca::carregarMembros(string nomeArquivo)
{
  if (!arquivoExiste(nomeArquivo))
  {
    cerr << "Arquivo " << nomeArquivo << " não encontrado." << endl;
    return;
  }

  ifstream arquivo(nomeArquivo);
  string linha;

  while (getline(arquivo, linha))
  {
    // formato da linha: ID1;Nome1;[ISBN1,ISBN2,...]
    string id = linha.substr(0, linha.find(';'));
    linha = linha.substr(linha.find(';') + 1);
    string nome = linha.substr(0, linha.find(';'));
    linha = linha.substr(linha.find(';') + 1);

    int ID = stoi(id);

    // remove os colchetes
    linha = linha.substr(1, linha.size() - 2);

    vector<string> ISBNs; // vetor para armazenar os ISBNs deste membro

    while (linha.find(',') != string::npos)
    {
      ISBNs.push_back(linha.substr(0, linha.find(',')));
      linha = linha.substr(linha.find(',') + 1);
    }

    ISBNs.push_back(linha);

    Membro membro(ID, nome);

    for (int j = 0; j < ISBNs.size(); j++)
    {
      for (int k = 0; k < this->livros.size(); k++)
      {
        if (this->livros[k].getISBN() == ISBNs[j])
        {
          this->emprestarLivro(membro.getID(), ISBNs[j]);
        }
      }
    }
  }
}

void Biblioteca::gravarMembros(string nomeArquivo)
{

  ofstream arquivo(nomeArquivo);
  if (arquivo.is_open())
  {
    for (int i = 0; i < this->membros.size(); i++)
    {
      // Construir a linha no formato: ID;Nome;[ISBN1,ISBN2,...]
      arquivo << this->membros[i].getID() << ";"
              << this->membros[i].getNome() << ";[";

      // Adicionar os ISBNs separados por vírgulas
      vector<string> ISBNs;

      for (int j = 0; j < this->membros[i].getLivrosEmprestados().size(); ++j)
      {
        ISBNs.push_back(this->membros[i].getLivrosEmprestados()[j].getISBN());
      }

      for (size_t j = 0; j < ISBNs.size(); ++j)
      {
        arquivo << ISBNs[j];
        if (j < ISBNs.size() - 1)
        {
          arquivo << ",";
        }
      }
      arquivo << "]\n"; // Fechar a linha com o caractere de nova linha
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

void Biblioteca::gravarLivros(string nomeArquivo)
{

  ofstream arquivo(nomeArquivo);
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
      for (int j = 0; j < this->membros[i].getLivrosEmprestados().size(); j++)
      {
        if (this->membros[i].getLivrosEmprestados()[j].getISBN() == ISBN)
        {
          this->membros[i].getLivrosEmprestados()[j].devolver();
          this->membros[i].getLivrosEmprestados().erase(this->membros[i].getLivrosEmprestados().begin() + j);
        }
      }
    }
  }
}