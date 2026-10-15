#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP

#include <map>
#include <string>
#include <vector>

#include "Produto.hpp"
#include "Secao.hpp"
#include "Status.hpp"

class Estoque {
private:
    std::map<std::string, Secao> m_secoes;

public:
    Status criarSecao(const std::string &nome);

    Status adicionarProduto(const Produto &produto, const std::string &secao);
    Status removerProduto(const std::string &nome, const std::string &secao);
    Status modificarPreco(const std::string &nome, double novoPreco,
                          const std::string &secao);
    Status modificarQuantidade(const std::string &nome, int novaQnt,
                               const std::string &secao);
    Status buscarProduto(const std::string &nome, const std::string &secao,
                         std::vector<Produto> &saida) const;

    bool vazio() const;
    const std::map<std::string, Secao> &getSecoes() const;
};

#endif
