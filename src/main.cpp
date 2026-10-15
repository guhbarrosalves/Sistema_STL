#include "Estoque.hpp"
#include "Interface.hpp"

int main() {
    Estoque estoque;
    Interface interface(estoque);
    interface.executar();
    return 0;
}
