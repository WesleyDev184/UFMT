#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isPalindrome(const string& str) {
    string reversed = str;
    reverse(reversed.begin(), reversed.end());
    return str == reversed;
}

int main() {
    string str;

    // Solicita a entrada do usuário
    cout << "Digite uma string para verificar se é um palíndromo: ";
    cin >> str;

    // Verifica se a string é um palíndromo
    if (isPalindrome(str)) {
        cout << "\"" << str << "\" é um palíndromo." << endl;
    } else {
        cout << "\"" << str << "\" não é um palíndromo." << endl;
    }

    return 0;
}
