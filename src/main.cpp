#include <iostream>
#include "Produto.hpp"

int main() {
    Produto p1("Cafe - Kimimo", 10, 5.50);
    Produto p2("Arroz - Tio Joao", 5, 4.00);
    Produto p3("Cafe - Kimimo", 2, 6.00);

    // Teste operator<
    if (p1 < p2) {
        std::cout << "p1 < p2: true" << std::endl;
    } else {
        std::cout << "p1 < p2: false" << std::endl;
    }

    if (p2 < p1) {
        std::cout << "p2 < p1: true" << std::endl;
    } else {
        std::cout << "p2 < p1: false" << std::endl;
    }

    // Teste operator==
    if (p1 == p3) {
        std::cout << "p1 == p3: true (mesmo nome)" << std::endl;
    } else {
        std::cout << "p1 == p3: false" << std::endl;
    }

    if (p1 == p2) {
        std::cout << "p1 == p2: true" << std::endl;
    } else {
        std::cout << "p1 == p2: false" << std::endl;
    }

    return 0;
}
