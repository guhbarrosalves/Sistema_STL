#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Estoque.hpp"

class Interface {
private:
    Estoque &m_estoque;
    void mostrarAjuda() const;

public:
    // Construtor de interface.
    // explicit bloqueia a conversão automática do Estoque para uma interface, apenas quando é escrito Interface(Estoque &estoque)
    explicit Interface(Estoque &estoque);
    void executar();

};

#endif
