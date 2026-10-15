#ifndef SECAO_HPP
#define SECAO_HPP

#include <set>
#include <string>
#include <vector>

#include "Produto.hpp"
#include "Status.hpp"

class Secao {
private:
    std::string m_nome;
    std::set<Produto> m_produtos;

public:
    Secao(const std::string &nome);

    const std::string &getNome() const;

    Status adicionar(const Produto &produto);
    Status remover(const std::string &nome);
    Status modificarPreco(const std::string &nome, double novoPreco);
    Status modificarQuantidade(const std::string &nome, int novaQnt);
    Status buscar(const std::string &nome, std::vector<Produto> &saida) const;

    bool vazia() const;
    const std::set<Produto> &getProdutos() const;
};

#endif
