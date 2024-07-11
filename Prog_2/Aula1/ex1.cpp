#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Digite a quantidade de números: ";
    cin >> N;

    double soma = 0;
    for (int i = 0; i < N; ++i) {
        double num;
        cout << "Digite um número: ";
        cin >> num;
        soma += num;
    }

    double media = soma / N;
    cout << "Soma: " << soma << endl;
    cout << "Média: " << media << endl;

    return 0;
}
