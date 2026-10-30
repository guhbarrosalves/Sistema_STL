#include "Arquivo.hpp"
#include "Estoque.hpp"
#include "Interface.hpp"

int main() {
    Estoque estoque;
    Arquivo arquivo("estoque.txt");

    arquivo.load(estoque);

    Interface interface(estoque);
    interface.executar();

    arquivo.save(estoque);
    return 0;
}
