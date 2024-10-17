#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

template <typename T>
class Registro
{
private:
  struct Aluno
  {
    string nome;
    T nota;
  };

  vector<Aluno> alunos;

public:
  void adicionarAluno(const string &nome, T nota)
  {
    alunos.push_back({nome, nota});
  }

  double calcularMedia() const
  {
    if (alunos.empty())
      return 0.0;
    T soma = accumulate(alunos.begin(), alunos.end(), T(0),
                        [](T acc, const Aluno &aluno)
                        {
                          return acc + aluno.nota;
                        });
    return static_cast<double>(soma) / alunos.size();
  }

  void exibirAlunos() const
  {
    cout << "Lista de Alunos:\n";
    for (const auto &aluno : alunos)
    {
      cout << "Nome: " << aluno.nome << ", Nota: " << aluno.nota << '\n';
    }
  }
};

int main()
{
  Registro<int> registroInt;
  registroInt.adicionarAluno("João", 85);
  registroInt.adicionarAluno("Maria", 90);
  registroInt.adicionarAluno("Carlos", 75);

  cout << "Alunos (Notas inteiras):\n";
  registroInt.exibirAlunos();
  cout << "Média das notas: " << registroInt.calcularMedia() << "\n\n";

  Registro<float> registroFloat;
  registroFloat.adicionarAluno("Ana", 85.5f);
  registroFloat.adicionarAluno("Pedro", 91.3f);
  registroFloat.adicionarAluno("Lucas", 78.2f);

  cout << "Alunos (Notas float):\n";
  registroFloat.exibirAlunos();
  cout << "Média das notas: " << registroFloat.calcularMedia() << "\n\n";

  Registro<double> registroDouble;
  registroDouble.adicionarAluno("Fernanda", 89.75);
  registroDouble.adicionarAluno("Roberto", 92.1);
  registroDouble.adicionarAluno("Bianca", 84.6);

  cout << "Alunos (Notas double):\n";
  registroDouble.exibirAlunos();
  cout << "Média das notas: " << registroDouble.calcularMedia() << "\n";

  return 0;
}
