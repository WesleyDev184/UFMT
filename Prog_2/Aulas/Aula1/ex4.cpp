#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Digite um número inteiro positivo: ";
    cin >> num;

    if (num < 0) {
        cout << "Número inválido!" << endl;
        return 1;
    }

    unsigned long long fatorial = 1;
    for (int i = 1; i <= num; ++i) {
        fatorial *= i;
    }

    cout << "Fatorial de " << num << " é: " << fatorial << endl;

    return 0;
}
