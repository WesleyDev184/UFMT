#include <iostream>

using namespace std;

void reset(int &cwin) {
    cwin = 1;
}

void incrementa(int &cwin) {
    cwin += 1;
}

void dobra(int &cwin) {
    cwin *= 2;
    if (cwin > 100) {
        cwin = 100;
    }
}

int main() {
    int instantes_de_perda[3];
    cout << "Informe os instantes de tempo onde ocorrerão as perdas: ";
    for (int i = 0; i < 3; i++) {
        cin >> instantes_de_perda[i];
    }

    int cwin = 1; // Inicializa a janela de congestionamento em 1
    int limite = 100; // Limite máximo de iterações

    cout << "Seg | Cwin" << endl;

    for (int seg = 1; seg <= limite; seg++) {
        bool perda = false;
        for (int i = 0; i < 3; i++) {
            if (seg == instantes_de_perda[i]) {
                perda = true;
                break;
            }
        }

        if (perda) {
            cout << seg << " | perda" << endl;
            reset(cwin);
        } else {
            cout << seg << " | " << cwin << endl;

            if (seg % 6 == 0) {
                dobra(cwin);
            } else {
                incrementa(cwin);
            }
        }
    }

    return 0;
}
