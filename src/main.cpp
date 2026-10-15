#include <iostream>
#include <vector>

#include "Produto.hpp"
#include "Secao.hpp"
#include "Status.hpp"

// Temporário: só para o teste da Etapa 2. Na Etapa 4 a Interface fará isso.
void imprimirStatus(Status s) {
    if (s == OK) {
        std::cout << "OK" << std::endl;
    } else if (s == PRODUTO_EXISTENTE) {
        std::cout << "PRODUTO_EXISTENTE" << std::endl;
    } else if (s == PRODUTO_INEXISTENTE) {
        std::cout << "PRODUTO_INEXISTENTE" << std::endl;
    } else if (s == VALOR_INVALIDO) {
        std::cout << "VALOR_INVALIDO" << std::endl;
    } else if (s == VALOR_IGUAL) {
        std::cout << "VALOR_IGUAL" << std::endl;
    } else if (s == ARGUMENTO_INVALIDO) {
        std::cout << "ARGUMENTO_INVALIDO" << std::endl;
    }
}

void imprimirProdutos(const std::vector<Produto> &produtos) {
    if (produtos.empty()) {
        std::cout << "  (nenhum)" << std::endl;
        return;
    }
    for (std::vector<Produto>::size_type i = 0; i < produtos.size(); ++i) {
        std::cout << "  " << produtos[i].getNome()
                  << " | qnt: " << produtos[i].getQuantidade()
                  << " | preco: " << produtos[i].getPreco() << std::endl;
    }
}

int main() {
    Secao secao("Mercearia");
    std::cout << "vazia no inicio: " << (secao.vazia() ? "sim" : "nao") << std::endl;

    std::cout << "add Cafe - Kimimo: ";
    imprimirStatus(secao.adicionar(Produto("Cafe - Kimimo", 10, 5.50)));

    std::cout << "add Arroz - Tio Joao: ";
    imprimirStatus(secao.adicionar(Produto("Arroz - Tio Joao", 5, 4.00)));

    std::cout << "add Cafe - Kimimo de novo: ";
    imprimirStatus(secao.adicionar(Produto("Cafe - Kimimo", 2, 6.00)));

    std::cout << "add Cafe (sem marca): ";
    imprimirStatus(secao.adicionar(Produto("Cafe", 3, 2.00)));

    std::cout << "add Sal - Cypress com qnt 0: ";
    imprimirStatus(secao.adicionar(Produto("Sal - Cypress", 0, 1.00)));

    std::cout << "modificarPreco Cafe - Kimimo para 6.00: ";
    imprimirStatus(secao.modificarPreco("Cafe - Kimimo", 6.00));

    std::cout << "modificarPreco Cafe - Kimimo para 6.00 de novo: ";
    imprimirStatus(secao.modificarPreco("Cafe - Kimimo", 6.00));

    std::cout << "modificarPreco Cafe - Kimimo para -1: ";
    imprimirStatus(secao.modificarPreco("Cafe - Kimimo", -1));

    std::cout << "modificarPreco Chocolate - Lacta (nao existe): ";
    imprimirStatus(secao.modificarPreco("Chocolate - Lacta", 3.00));

    std::cout << "modificarQuantidade Arroz - Tio Joao para 8: ";
    imprimirStatus(secao.modificarQuantidade("Arroz - Tio Joao", 8));

    std::cout << "modificarQuantidade Arroz - Tio Joao para 8 de novo: ";
    imprimirStatus(secao.modificarQuantidade("Arroz - Tio Joao", 8));

    std::cout << "buscar Cafe - Kimimo (exata):" << std::endl;
    std::vector<Produto> achados;
    imprimirStatus(secao.buscar("Cafe - Kimimo", achados));
    imprimirProdutos(achados);

    std::cout << "buscar Cafe (parcial):" << std::endl;
    imprimirStatus(secao.buscar("Cafe", achados));
    imprimirProdutos(achados);

    std::cout << "buscar Arroz (parcial):" << std::endl;
    imprimirStatus(secao.buscar("Arroz", achados));
    imprimirProdutos(achados);

    std::cout << "buscar Feijao (parcial, nao existe):" << std::endl;
    imprimirStatus(secao.buscar("Feijao", achados));
    imprimirProdutos(achados);

    std::cout << "remover Cafe - Kimimo: ";
    imprimirStatus(secao.remover("Cafe - Kimimo"));

    std::cout << "remover Cafe - Kimimo de novo: ";
    imprimirStatus(secao.remover("Cafe - Kimimo"));

    std::cout << "produtos restantes (ordem do set):" << std::endl;
    const std::set<Produto> &todos = secao.getProdutos();
    for (std::set<Produto>::const_iterator it = todos.begin();
         it != todos.end(); ++it) {
        std::cout << "  " << it->getNome()
                  << " | qnt: " << it->getQuantidade()
                  << " | preco: " << it->getPreco() << std::endl;
    }

    std::cout << "vazia no fim: " << (secao.vazia() ? "sim" : "nao") << std::endl;

    return 0;
}
