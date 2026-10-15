#include "Estoque.hpp"

Status Estoque::criarSecao(const std::string &nome) {
    if (nome.empty()) {
        return ARGUMENTO_INVALIDO;
    }
    if (m_secoes.find(nome) != m_secoes.end()) {
        return SECAO_EXISTENTE;
    }
    // insert e nunca operator[]: o [] criaria uma Secao vazia sem querer,
    // e Secao não tem construtor padrão
    m_secoes.insert(std::make_pair(nome, Secao(nome)));
    return OK;
}

Status Estoque::adicionarProduto(const Produto &produto,
                                 const std::string &secao) {
    // Seção conferida primeiro (decisão 10); achando, delega para a Secao
    std::map<std::string, Secao>::iterator it = m_secoes.find(secao);
    if (it == m_secoes.end()) {
        return SECAO_INEXISTENTE;
    }
    return it->second.adicionar(produto);
}

Status Estoque::removerProduto(const std::string &nome,
                               const std::string &secao) {
    std::map<std::string, Secao>::iterator it = m_secoes.find(secao);
    if (it == m_secoes.end()) {
        return SECAO_INEXISTENTE;
    }
    return it->second.remover(nome);
}

Status Estoque::modificarPreco(const std::string &nome, double novoPreco,
                               const std::string &secao) {
    std::map<std::string, Secao>::iterator it = m_secoes.find(secao);
    if (it == m_secoes.end()) {
        return SECAO_INEXISTENTE;
    }
    return it->second.modificarPreco(nome, novoPreco);
}

Status Estoque::modificarQuantidade(const std::string &nome, int novaQnt,
                                    const std::string &secao) {
    std::map<std::string, Secao>::iterator it = m_secoes.find(secao);
    if (it == m_secoes.end()) {
        return SECAO_INEXISTENTE;
    }
    return it->second.modificarQuantidade(nome, novaQnt);
}

Status Estoque::buscarProduto(const std::string &nome,
                              const std::string &secao,
                              std::vector<Produto> &saida) const {
    std::map<std::string, Secao>::const_iterator it = m_secoes.find(secao);
    if (it == m_secoes.end()) {
        saida.clear(); // não deixa a busca anterior aparecer como resultado
        return SECAO_INEXISTENTE;
    }
    return it->second.buscar(nome, saida);
}

bool Estoque::vazio() const {
    return m_secoes.empty();
}

const std::map<std::string, Secao> &Estoque::getSecoes() const {
    return m_secoes;
}
