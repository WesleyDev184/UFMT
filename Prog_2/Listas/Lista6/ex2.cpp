#include <iostream>

class Vector2D {
private:
    double x, y;

public:
    // Construtores
    Vector2D() : x(0), y(0) {}
    Vector2D(double x, double y) : x(x), y(y) {}

    // Sobrecarga do operador +
    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    // Sobrecarga do operador -
    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    // Sobrecarga do operador ==
    bool operator==(const Vector2D& v) const {
        return x == v.x && y == v.y;
    }

    // Sobrecarga do operador <<
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // Sobrecarga do operador >>
    friend std::istream& operator>>(std::istream& is, Vector2D& v) {
        is >> v.x >> v.y;
        return is;
    }
};

int main() {
    Vector2D v1(3.5, 2.0);
    Vector2D v2(1.5, 4.0);

    // Adiciona dois vetores
    Vector2D v3 = v1 + v2;
    std::cout << "Soma de v1 e v2: " << v3 << std::endl;

    // Subtrai dois vetores
    Vector2D v4 = v1 - v2;
    std::cout << "Diferenca entre v1 e v2: " << v4 << std::endl;

    // Compara dois vetores
    if (v1 == v2) {
        std::cout << "v1 e v2 sao iguais." << std::endl;
    } else {
        std::cout << "v1 e v2 sao diferentes." << std::endl;
    }

    // Leitura de vetor
    Vector2D v5;
    std::cout << "Digite um vetor (formato: x y): ";
    std::cin >> v5;
    std::cout << "Vetor lido: " << v5 << std::endl;

    return 0;
}
