#include "Arquivo.hpp"

#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include "Produto.hpp"
#include "Secao.hpp"

Arquivo::Arquivo(const std::string &caminho) : m_caminho(caminho) {}

void Arquivo::save(const Estoque &estoque) const {
    std::ofstream arquivo(m_caminho.c_str());
    if (!arquivo.is_open()) {
        return;
    }

    arquivo << std::fixed << std::setprecision(2);

    std::map<std::string, Secao>::const_iterator itSecao;
    for (itSecao = estoque.getSecoes().begin();
         itSecao != estoque.getSecoes().end(); ++itSecao) {
        const Secao &secao = itSecao->second;
        const std::set<Produto> &produtos = secao.getProdutos();

        if (produtos.empty()) {
            arquivo << secao.getNome() << ";;;" << "\n";
            continue;
        }

        std::set<Produto>::const_iterator itProduto;
        for (itProduto = produtos.begin(); itProduto != produtos.end();
             ++itProduto) {
            const Produto &produto = *itProduto;
            arquivo << secao.getNome() << ";"
                    << produto.getNome() << ";"
                    << produto.getPreco() << ";"
                    << produto.getQuantidade() << "\n";
        }
    }
}

void Arquivo::load(Estoque &estoque) const {
    std::ifstream arquivo(m_caminho.c_str());
    if (!arquivo.is_open()) {
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        std::string secaoNome;
        std::string produtoNome;
        std::string precoTexto;
        std::string qntTexto;

        if (!std::getline(iss, secaoNome, ';')) {
            continue;
        }

        std::getline(iss, produtoNome, ';');
        std::getline(iss, precoTexto, ';');
        std::getline(iss, qntTexto, ';');

        if (produtoNome.empty()) {
            estoque.criarSecao(secaoNome);
            continue;
        }

        std::istringstream fluxoPreco(precoTexto);
        double preco;
        fluxoPreco >> preco;

        std::istringstream fluxoQnt(qntTexto);
        int quantidade;
        fluxoQnt >> quantidade;

        Produto produto(produtoNome, quantidade, preco);
        estoque.criarSecao(secaoNome);
        estoque.adicionarProduto(produto, secaoNome);
    }
}
