#include <iostream>
#include <string>

// Definição do enumerador DiasDaSemana
enum DiasDaSemana
{
  Domingo,
  SegundaFeira,
  TercaFeira,
  QuartaFeira,
  QuintaFeira,
  SextaFeira,
  Sabado
};

// Função que recebe um valor do enumerador e retorna o nome do dia como string
std::string nomeDoDia(DiasDaSemana dia)
{
  switch (dia)
  {
  case Domingo:
    return "Domingo";
  case SegundaFeira:
    return "Segunda-feira";
  case TercaFeira:
    return "Terça-feira";
  case QuartaFeira:
    return "Quarta-feira";
  case QuintaFeira:
    return "Quinta-feira";
  case SextaFeira:
    return "Sexta-feira";
  case Sabado:
    return "Sábado";
  default:
    return "Dia inválido!";
  }
}

int main()
{
  try
  {
    int dia;

    // Entrada do usuário
    std::cout << "Digite um número para o dia da semana (0 para Domingo, 6 para Sábado): ";
    std::cin >> dia;

    // Verifica se o valor de entrada está dentro do intervalo válido
    if (dia < 0 || dia > 6)
    {
      throw std::out_of_range("Valor fora do intervalo permitido!");
    }
    else
    {
      // Converte o número inteiro para o enumerador DiasDaSemana
      DiasDaSemana diaSelecionado = static_cast<DiasDaSemana>(dia);

      // Exibe o nome do dia correspondente
      std::cout << "O dia selecionado é: " << nomeDoDia(diaSelecionado) << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
