#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Digite a quantidade de números pares: ";
    cin >> N;

    int soma = 0;
    for (int i = 1; i <= N; ++i) {
        soma += 2 * i;
    }

    cout << "A soma dos " << N << " primeiros números pares é: " << soma << endl;

    return 0;
}
