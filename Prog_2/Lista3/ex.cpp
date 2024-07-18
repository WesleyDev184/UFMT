#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

// Estrutura de dados
struct Usuario {
    string nome;
    vector<weak_ptr<Usuario>> dependencias;
    unique_ptr<int> recursoExclusivo;

    Usuario(const string& nome_) : nome(nome_), recursoExclusivo(make_unique<int>(0)) {
        cout << "Usuario '" << nome << "' adicionado." << endl;
    }
};

// Vetor global de usuários
vector<shared_ptr<Usuario>> usuarios;

// Protótipos das funções
void adicionarUsuario(const string& nome);
void adicionarDependencia(const string& nomeUsuario, const string& nomeDependencia);
void listarDependencias(const string& nomeUsuario);
void atribuirRecursoExclusivo(const string& nomeUsuario, int valor);
shared_ptr<Usuario> encontrarUsuario(const string& nome);

// Implementações das funções

void adicionarUsuario(const string& nome) {
    usuarios.push_back(make_shared<Usuario>(nome));
}

shared_ptr<Usuario> encontrarUsuario(const string& nome) {
    for (const auto& u : usuarios) {
        if (u->nome == nome) {
            return u;
        }
    }
    return nullptr;
}

void adicionarDependencia(const string& nomeUsuario, const string& nomeDependencia) {
    auto usuario = encontrarUsuario(nomeUsuario);
    auto dependencia = encontrarUsuario(nomeDependencia);

    if (usuario && dependencia) {
        usuario->dependencias.push_back(dependencia);
        cout << "Usuario '" << nomeDependencia << "' adicionado como dependencia de '" << nomeUsuario << "'." << endl;
    }
}

void listarDependencias(const string& nomeUsuario) {
    auto usuario = encontrarUsuario(nomeUsuario);

    if (usuario) {
        cout << "Dependências de '" << usuario->nome << "':" << endl;
        if (usuario->dependencias.empty()) {
            cout << "- Nenhuma" << endl;
        } else {
            for (const auto& dep : usuario->dependencias) {
                if (auto dependente = dep.lock()) {
                    cout << "- " << dependente->nome << endl;
                }
            }
        }
    }
}

void atribuirRecursoExclusivo(const string& nomeUsuario, int valor) {
    auto usuario = encontrarUsuario(nomeUsuario);

    if (usuario) {
        *usuario->recursoExclusivo = valor;
        cout << "Recurso exclusivo de '" << usuario->nome << "' atribuído com valor: " << valor << "." << endl;
    }
}

// Programa principal
int main() {
    adicionarUsuario("Alice");
    adicionarUsuario("Bob");
    adicionarUsuario("Carol");
    
    adicionarDependencia("Alice", "Bob");
    adicionarDependencia("Alice", "Carol");
    
    atribuirRecursoExclusivo("Alice", 42);
    
    listarDependencias("Alice");
    listarDependencias("Bob");
    
    return 0;
}
