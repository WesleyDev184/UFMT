#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Digite a quantidade de números quadrados: ";
    cin >> N;

    for (int i = 1; i <= N; ++i) {
        cout << i * i << " ";
    }
    cout << endl;

    return 0;
}
