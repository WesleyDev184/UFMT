#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Aluno
{
private:
  string nome;
  int matricula;
  string curso;
  vector<float> notas;

public:
  Aluno()
  {
    nome = "";
    matricula = 0;
    curso = "";
    notas = {};
  }

  Aluno(string nome, int matricula, string curso, vector<float> notas)
  {
    this->nome = nome;
    this->matricula = matricula;
    this->curso = curso;
    this->notas = notas;
  }

  void setNome(string nome)
  {
    this->nome = nome;
  }

  void setMatricula(int matricula)
  {
    this->matricula = matricula;
  }

  void setCurso(string curso)
  {
    this->curso = curso;
  }

  void setNota(float nota)
  {
    notas.push_back(nota);
  }

  string getNome()
  {
    return nome;
  }

  int getMatricula()
  {
    return matricula;
  }

  string getCurso()
  {
    return curso;
  }

  vector<float> getNotas()
  {
    return notas;
  }

  float calcularMedia()
  {
    float media = 0;
    for (int i = 0; i < notas.size(); i++)
    {
      media += notas[i];
    }
    return media / notas.size();
  }

  bool verificarAprovacao()
  {
    return this->calcularMedia() >= 7.0;
  }

  void mostrarDados()
  {
    cout << "Nome : " << nome << ", Matricula : " << matricula << ", Curso : " << curso << ", Nota : " << this->calcularMedia() << endl;
  }
};

int main()
{
  vector<float> notas = {7.5, 8.0, 6.5};
  Aluno a1("Maria Silva", 202345, "Engenharia", notas);
  a1.mostrarDados();                                                           // Nome : Maria Silva , Matricula : 202345 , Curso :Engenharia, Nota : 7.5
  cout << " Media : " << a1.calcularMedia() << endl;                           // Media :7.5
  cout << " Aprovado : " << (a1.verificarAprovacao() ? "Sim" : "No ") << endl; // Aprovado : Sim
  return 0;
}