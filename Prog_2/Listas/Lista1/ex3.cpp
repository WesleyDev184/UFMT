#include <iostream>
#include <string>

using namespace std;

bool busca_substring(const string &str, const string &substr, int &pos) {
    pos = str.find(substr);
    return (pos != string::npos);
}

int main() {
    string str = "JANELA";
    string substr = "NELA";
    int pos;

    if (busca_substring(str, substr, pos)) {
        cout << "Substring encontrada na posição: " << pos << endl;
    } else {
        cout << "Substring não encontrada." << endl;
    }

    return 0;
}
