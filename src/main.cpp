#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "Estoque.hpp"
#include "Produto.hpp"
#include "Secao.hpp"
#include "Status.hpp"

// Temporário: só para o teste da Etapa 3. Na Etapa 4 a Interface fará isso.
void imprimirStatus(Status s) {
    if (s == OK) {
        std::cout << "OK" << std::endl;
    } else if (s == SECAO_EXISTENTE) {
        std::cout << "SECAO_EXISTENTE" << std::endl;
    } else if (s == SECAO_INEXISTENTE) {
        std::cout << "SECAO_INEXISTENTE" << std::endl;
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

void imprimirEstoque(const Estoque &estoque) {
    if (estoque.vazio()) {
        std::cout << "  (estoque vazio)" << std::endl;
        return;
    }
    const std::map<std::string, Secao> &secoes = estoque.getSecoes();
    std::map<std::string, Secao>::const_iterator it;
    for (it = secoes.begin(); it != secoes.end(); ++it) {
        std::cout << "  " << it->first << ":" << std::endl;
        const std::set<Produto> &produtos = it->second.getProdutos();
        if (produtos.empty()) {
            std::cout << "    (nenhum produto)" << std::endl;
        }
        std::set<Produto>::const_iterator p;
        for (p = produtos.begin(); p != produtos.end(); ++p) {
            std::cout << "    " << p->getNome()
                      << " | qnt: " << p->getQuantidade()
                      << " | preco: " << p->getPreco() << std::endl;
        }
    }
}

int main() {
    Estoque estoque;

    std::cout << "vazio no inicio: " << (estoque.vazio() ? "sim" : "nao")
              << std::endl;

    std::cout << "criarSecao Mercearia: ";
    imprimirStatus(estoque.criarSecao("Mercearia"));

    std::cout << "criarSecao Mercearia de novo: ";
    imprimirStatus(estoque.criarSecao("Mercearia"));

    std::cout << "criarSecao \"\" (vazia): ";
    imprimirStatus(estoque.criarSecao(""));

    std::cout << "criarSecao Bebidas: ";
    imprimirStatus(estoque.criarSecao("Bebidas"));

    std::cout << "add Cafe - Kimimo na secao NaoExiste: ";
    imprimirStatus(
        estoque.adicionarProduto(Produto("Cafe - Kimimo", 10, 5.50), "NaoExiste"));

    std::cout << "add Cafe - Kimimo na Mercearia: ";
    imprimirStatus(
        estoque.adicionarProduto(Produto("Cafe - Kimimo", 10, 5.50), "Mercearia"));

    std::cout << "add Cafe - Kimimo de novo: ";
    imprimirStatus(
        estoque.adicionarProduto(Produto("Cafe - Kimimo", 2, 6.00), "Mercearia"));

    std::cout << "add Cafe (sem marca) na Mercearia: ";
    imprimirStatus(
        estoque.adicionarProduto(Produto("Cafe", 3, 2.00), "Mercearia"));

    std::cout << "add Arroz - Tio Joao na Mercearia: ";
    imprimirStatus(
        estoque.adicionarProduto(Produto("Arroz - Tio Joao", 5, 4.00), "Mercearia"));

    std::cout << "add Agua - Minalba em Bebidas: ";
    imprimirStatus(
        estoque.adicionarProduto(Produto("Agua - Minalba", 20, 2.50), "Bebidas"));

    std::cout << "remover Cafe - Kimimo na NaoExiste: ";
    imprimirStatus(estoque.removerProduto("Cafe - Kimimo", "NaoExiste"));

    std::cout << "remover Chocolate - Lacta (nao existe) na Mercearia: ";
    imprimirStatus(estoque.removerProduto("Chocolate - Lacta", "Mercearia"));

    std::cout << "remover Cafe - Kimimo da Mercearia: ";
    imprimirStatus(estoque.removerProduto("Cafe - Kimimo", "Mercearia"));

    std::cout << "modificarPreco Arroz - Tio Joao para 4.50 na NaoExiste: ";
    imprimirStatus(estoque.modificarPreco("Arroz - Tio Joao", 4.50, "NaoExiste"));

    std::cout << "modificarPreco Arroz - Tio Joao para 4.50 na Mercearia: ";
    imprimirStatus(estoque.modificarPreco("Arroz - Tio Joao", 4.50, "Mercearia"));

    std::cout << "modificarPreco Arroz - Tio Joao para 4.50 de novo: ";
    imprimirStatus(estoque.modificarPreco("Arroz - Tio Joao", 4.50, "Mercearia"));

    std::cout << "modificarPreco Arroz - Tio Joao para -1: ";
    imprimirStatus(estoque.modificarPreco("Arroz - Tio Joao", -1, "Mercearia"));

    std::cout << "modificarQuantidade Arroz - Tio Joao para 8: ";
    imprimirStatus(estoque.modificarQuantidade("Arroz - Tio Joao", 8, "Mercearia"));

    std::cout << "modificarQuantidade Arroz - Tio Joao para 8 de novo: ";
    imprimirStatus(estoque.modificarQuantidade("Arroz - Tio Joao", 8, "Mercearia"));

    std::cout << "buscar Arroz (parcial) na Mercearia:" << std::endl;
    std::vector<Produto> achados;
    imprimirStatus(estoque.buscarProduto("Arroz", "Mercearia", achados));
    for (std::vector<Produto>::size_type i = 0; i < achados.size(); ++i) {
        std::cout << "  " << achados[i].getNome()
                  << " | qnt: " << achados[i].getQuantidade()
                  << " | preco: " << achados[i].getPreco() << std::endl;
    }

    std::cout << "buscar Arroz na NaoExiste (deve limpar o vetor): ";
    imprimirStatus(estoque.buscarProduto("Arroz", "NaoExiste", achados));
    std::cout << "  achados depois: " << achados.size() << std::endl;

    std::cout << "buscar Feijao (nao existe) na Mercearia: ";
    imprimirStatus(estoque.buscarProduto("Feijao", "Mercearia", achados));

    std::cout << "vazio no fim: " << (estoque.vazio() ? "sim" : "nao")
              << std::endl;

    std::cout << "estoque completo (ordem do map):" << std::endl;
    imprimirEstoque(estoque);

    return 0;
}
