#include "Secao.hpp"

#include <algorithm>

namespace {
const std::string SEPARADOR = " - ";
}

Secao::Secao(const std::string &nome)
    : m_nome(nome) {}

const std::string &Secao::getNome() const {
    return m_nome;
}

Status Secao::adicionar(const Produto &produto) {
    if (produto.getNome().find(SEPARADOR) == std::string::npos) {
        return ARGUMENTO_INVALIDO;
    }
    if (produto.getQuantidade() <= 0 || produto.getPreco() <= 0) {
        return VALOR_INVALIDO;
    }
    if (m_produtos.find(produto) != m_produtos.end()) {
        return PRODUTO_EXISTENTE;
    }
    m_produtos.insert(produto);
    return OK;
}

Status Secao::remover(const std::string &nome) {
    // O operator< compara só o nome, então a chave temporária acha pelo nome
    Produto chave(nome, 0, 0);
    std::set<Produto>::iterator it = m_produtos.find(chave);
    if (it == m_produtos.end()) {
        return PRODUTO_INEXISTENTE;
    }
    m_produtos.erase(it);
    return OK;
}

Status Secao::modificarPreco(const std::string &nome, double novoPreco) {
    Produto chave(nome, 0, 0);
    std::set<Produto>::iterator it = m_produtos.find(chave);
    if (it == m_produtos.end()) {
        return PRODUTO_INEXISTENTE;
    }
    if (novoPreco <= 0) {
        return VALOR_INVALIDO;
    }
    if (novoPreco == it->getPreco()) {
        return VALOR_IGUAL;
    }
    // Elemento de set é const: copia, apaga e reinsere com o valor novo
    Produto atualizado(it->getNome(), it->getQuantidade(), novoPreco);
    m_produtos.erase(it);
    m_produtos.insert(atualizado);
    return OK;
}

Status Secao::modificarQuantidade(const std::string &nome, int novaQnt) {
    Produto chave(nome, 0, 0);
    std::set<Produto>::iterator it = m_produtos.find(chave);
    if (it == m_produtos.end()) {
        return PRODUTO_INEXISTENTE;
    }
    if (novaQnt <= 0) {
        return VALOR_INVALIDO;
    }
    if (novaQnt == it->getQuantidade()) {
        return VALOR_IGUAL;
    }
    Produto atualizado(it->getNome(), novaQnt, it->getPreco());
    m_produtos.erase(it);
    m_produtos.insert(atualizado);
    return OK;
}

Status Secao::buscar(const std::string &nome, std::vector<Produto> &saida) const {
    saida.clear();
    if (nome.find(SEPARADOR) != std::string::npos) {
        // Busca exata: std::find usa o operator== de Produto
        Produto chave(nome, 0, 0);
        std::set<Produto>::const_iterator it =
            std::find(m_produtos.begin(), m_produtos.end(), chave);
        if (it != m_produtos.end()) {
            saida.push_back(*it);
        }
    } else {
        // Busca parcial: compara o prefixo (antes do primeiro " - ")
        std::set<Produto>::const_iterator it;
        for (it = m_produtos.begin(); it != m_produtos.end(); ++it) {
            std::string completo = it->getNome();
            std::string::size_type pos = completo.find(SEPARADOR);
            std::string prefixo = completo.substr(0, pos);
            if (prefixo == nome) {
                saida.push_back(*it);
            }
        }
    }
    if (saida.empty()) {
        return PRODUTO_INEXISTENTE;
    }
    return OK;
}

bool Secao::vazia() const {
    return m_produtos.empty();
}

const std::set<Produto> &Secao::getProdutos() const {
    return m_produtos;
}
