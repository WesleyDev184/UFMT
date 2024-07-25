#include <iostream>
#include <string>

using namespace std;

class ContaBancaria
{
private:
  string numeroConta;
  float saldo;
  string titular;

public:
  ContaBancaria()
  {
    numeroConta = "";
    saldo = 0.0;
    titular = "";
  }

  ContaBancaria(string numeroConta, float saldo, string titular)
  {
    this->numeroConta = numeroConta;
    this->saldo = saldo;
    this->titular = titular;
  }

  void setNumeroConta(string numeroConta)
  {
    this->numeroConta = numeroConta;
  }

  void setSaldo(float saldo)
  {
    this->saldo = saldo;
  }

  void setTitular(string titular)
  {
    this->titular = titular;
  }

  string getNumeroConta()
  {
    return numeroConta;
  }

  float getSaldo()
  {
    return saldo;
  }

  string getTitular()
  {
    return titular;
  }

  void depositar(float valor)
  {
    saldo += valor;
  }

  void sacar(float valor)
  {
    saldo -= valor;
  }

  void mostrarDados()
  {
    cout << "Conta: " << numeroConta << ", Titular: " << titular << ", Saldo: " << saldo << endl;
  }
};

int main()
{
  ContaBancaria c1(" 12345-6 ", 1000.0, " Joao Silva ");
  c1.mostrarDados(); // Conta : 12345 -6 , Titular : Joao Silva , Saldo :1000 c1.depositar(500.0);
  c1.sacar(300.0);
  c1.mostrarDados(); // Conta : 12345 -6 , Titular : Joao Silva , Saldo :1200
  return 0;
}
