#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>

#include "Estoque.hpp"

class Interface {
private:
    Estoque &m_estoque;
    void mostrarAjuda() const;

    // Converte um campo da linha em número. Devolve false se o campo não for
    // um número puro (ex.: "abc", "5abc", "3,5").
    bool paraInteiro(const std::string &texto, int &valor) const;
    bool paraPreco(const std::string &texto, double &valor) const;

    // Imprime a mensagem correspondente ao status de um comando.
    // O nome é a seção ou o produto citado no comando.
    void mostrarStatus(Status status, const std::string &nome) const;

public:
    // Construtor de interface.
    // explicit bloqueia a conversão automática do Estoque para uma interface, apenas quando é escrito Interface(Estoque &estoque)
    explicit Interface(Estoque &estoque);
    void executar();

};

#endif
