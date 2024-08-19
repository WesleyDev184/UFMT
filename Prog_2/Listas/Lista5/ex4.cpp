#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Midia {
public:
    virtual void exibirInfo() const = 0;
    virtual void reproduzir() const = 0;
    virtual ~Midia() {}
};

class Livro : public Midia {
private:
    string titulo;
    string autor;
public:
    Livro(const string& t, const string& a) : titulo(t), autor(a) {}

    void exibirInfo() const override {
        cout << "Livro: " << titulo << " por " << autor << endl;
    }

    void reproduzir() const override {
        cout << "Abrindo o livro: " << titulo << endl;
    }
};

class CD : public Midia {
private:
    string titulo;
    string artista;
    int numeroDeFaixas;
public:
    CD(const string& t, const string& a, int n) : titulo(t), artista(a), numeroDeFaixas(n) {}

    void exibirInfo() const override {
        cout << "CD: " << titulo << " por " << artista << ", Número de faixas: " << numeroDeFaixas << endl;
    }

    void reproduzir() const override {
        cout << "Tocando CD: " << titulo << endl;
    }
};

class DVD : public Midia {
private:
    string titulo;
    string diretor;
    int duracao; 
public:
    DVD(const string& t, const string& d, int dur) : titulo(t), diretor(d), duracao(dur) {}

    void exibirInfo() const override {
        cout << "DVD: " << titulo << ", Dirigido por: " << diretor << ", Duração: " << duracao << " minutos" << endl;
    }

    void reproduzir() const override {
        cout << "Reproduzindo DVD: " << titulo << endl;
    }
};

int main() {
    vector<shared_ptr<Midia>> midias;

    midias.push_back(make_shared<Livro>("O Senhor dos Aneis", "J.R.R. Tolkien"));
    midias.push_back(make_shared<CD>("Thriller", "Michael Jackson", 9));
    midias.push_back(make_shared<DVD>("Inception", "Christopher Nolan", 148));

    for (const auto& midia : midias) {
        midia->exibirInfo();
        midia->reproduzir();
        cout << endl;
    }

    return 0;
}
