#include "Produto.hpp"

Produto::Produto(const std::string &nome, int quantidade, double preco)
    : m_nome(nome), m_quantidade(quantidade), m_preco(preco) {}

const std::string &Produto::getNome() const {
    return m_nome;
}

int Produto::getQuantidade() const {
    return m_quantidade;
}

double Produto::getPreco() const {
    return m_preco;
}

void Produto::setQuantidade(int quantidade) {
    m_quantidade = quantidade;
}

void Produto::setPreco(double preco) {
    m_preco = preco;
}

bool Produto::operator<(const Produto &outro) const {
    // Comparação definida pelo nome completo, sensível a maiúsculas
    return m_nome < outro.m_nome;
}

bool Produto::operator==(const Produto &outro) const {
    return m_nome == outro.m_nome;
}
