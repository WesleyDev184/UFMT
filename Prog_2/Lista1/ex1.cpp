#include <iostream>
#include <string>

bool temDoisNumeros(const std::string& senha) {
    int contador = 0;
    for (char c : senha) {
        if (c >= '0' && c <= '9') {
            contador++;
        }
    }
    return contador >= 2;
}

bool temCaractereEspecial(const std::string& senha) {
    std::string caracteresEspeciais = "@#%&$";
    for (char c : senha) {
        for (char especial : caracteresEspeciais) {
            if (c == especial) {
                return true;
            }
        }
    }
    return false;
}

bool temLetraMaiuscula(const std::string& senha) {
    for (char c : senha) {
        if (c >= 'A' && c <= 'Z') {
            return true;
        }
    }
    return false;
}

bool temLetraMinuscula(const std::string& senha) {
    for (char c : senha) {
        if (c >= 'a' && c <= 'z') {
            return true;
        }
    }
    return false;
}

bool validaSenha(const std::string& senha) {
    return temDoisNumeros(senha) && temCaractereEspecial(senha) && temLetraMaiuscula(senha) && temLetraMinuscula(senha);
}

void checaRequisitos(const std::string& senha) {
    if (!temDoisNumeros(senha)) {
        std::cout << "A senha deve conter pelo menos dois numeros." << std::endl;
    }
    if (!temCaractereEspecial(senha)) {
        std::cout << "A senha deve conter pelo menos um caractere especial (@, #, %, &, $)." << std::endl;
    }
    if (!temLetraMaiuscula(senha)) {
        std::cout << "A senha deve conter pelo menos uma letra maiuscula." << std::endl;
    }
    if (!temLetraMinuscula(senha)) {
        std::cout << "A senha deve conter pelo menos uma letra minuscula." << std::endl;
    }
}

int main() {
    std::string senha;

    while (true) {
        std::cout << "Digite uma senha: ";
        std::cin >> senha;

        if (validaSenha(senha)) {
            std::cout << "Senha válida!" << std::endl;
            break;
        } else {
            std::cout << "Senha inválida. Requisitos não atendidos:" << std::endl;
            checaRequisitos(senha);
        }
    }

    return 0;
}
