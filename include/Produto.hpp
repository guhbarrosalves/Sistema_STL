#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

class Produto {
private:
    std::string m_nome;
    int m_quantidade;
    double m_preco;

public:
    Produto(const std::string &nome, int quantidade, double preco);

    const std::string &getNome() const;
    int getQuantidade() const;
    double getPreco() const;

    void setQuantidade(int quantidade);
    void setPreco(double preco);

    // Compara SOMENTE o nome completo "nome - marca"
    bool operator<(const Produto &outro) const;
    bool operator==(const Produto &outro) const;
};

#endif
