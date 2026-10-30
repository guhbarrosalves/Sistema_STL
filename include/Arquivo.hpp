#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <string>

#include "Estoque.hpp"

// Unica classe que abre arquivo. Formato do registro:
// "secao;produto;preco;quantidade" (1 por linha).
// Secao sem produto: "nome;;;".
class Arquivo {
private:
    std::string m_caminho;

public:
    explicit Arquivo(const std::string &caminho);

    // Percorre o map de secoes e escreve 1 linha por registro.
    void save(const Estoque &estoque) const;

    // Le o registro, reconstrui Produto e repovoa o Estoque.
    // Arquivo inexistente: volta sem erro (primeira execucao).
    void load(Estoque &estoque) const;
};

#endif
