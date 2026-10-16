#include "Interface.hpp"

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

Interface::Interface(Estoque &estoque) : m_estoque(estoque) {}

void Interface::mostrarAjuda() const {
    std::cout << "Comandos disponiveis:" << std::endl;
    std::cout << " CRIAR_SECAO nome-da-secao" << std::endl;
    std::cout << " ADD_PRODUTO preco quantidade secao nome-do-produto"
              << std::endl;
    std::cout << " MOD_PRECO preco secao nome-do-produto" << std::endl;
    std::cout << " MOD_QNT quantidade secao nome-do-produto" << std::endl;
    std::cout << " REM_PROD secao nome-do-produto" << std::endl;
    std::cout << " BUSCAR_PROD secao nome-do-produto" << std::endl;
    std::cout << " ESTOQUE" << std::endl;
    std::cout << " FIM" << std::endl;
    std::cout << " -h, --help   mostra esta ajuda" << std::endl;
    std::cout << " Obs.: sem aspas; a secao e uma palavra so; o nome do"
              << " produto vem no fim e pode ter espacos"
              << " (ex.: Cafe - Kimimo)." << std::endl;
}

bool Interface::paraInteiro(const std::string &texto, int &valor) const {
    std::istringstream fluxo(texto);
    fluxo >> valor;
    if (fluxo.fail()) {
        return false;
    }
    // Se sobrar alguma coisa depois do número ("5abc"), o campo é inválido
    fluxo >> std::ws;
    return fluxo.eof();
}

bool Interface::paraPreco(const std::string &texto, double &valor) const {
    std::istringstream fluxo(texto);
    fluxo >> valor;
    if (fluxo.fail()) {
        return false;
    }
    fluxo >> std::ws;
    return fluxo.eof();
}

void Interface::mostrarStatus(Status status, const std::string &nome) const {
    switch (status) {
        case OK:
            break;
        case SECAO_EXISTENTE:
            std::cout << "Secao ja existe: " << nome << std::endl;
            break;
        case SECAO_INEXISTENTE:
            std::cout << "Secao inexistente: " << nome << std::endl;
            break;
        case PRODUTO_EXISTENTE:
            std::cout << "Produto ja existe na secao: " << nome
                      << ". Apenas preco e quantidade podem ser alterados."
                      << std::endl;
            break;
        case PRODUTO_INEXISTENTE:
            std::cout << "Produto nao encontrado: " << nome << std::endl;
            break;
        case VALOR_INVALIDO:
            std::cout << "Valor invalido para " << nome
                      << ": deve ser maior que zero." << std::endl;
            break;
        case VALOR_IGUAL:
            std::cout << "Valor igual ao atual em " << nome
                      << "; mantido o antigo." << std::endl;
            break;
        case ARGUMENTO_INVALIDO:
            std::cout << "Argumento invalido: " << nome << std::endl;
            break;
    }
}

void Interface::mostrarProduto(const Produto &produto) const {
    // fixed + setprecision(2) é o que faz o preço sair com duas casas (12.50)
    std::cout << produto.getNome()
              << " | preco: " << std::fixed << std::setprecision(2)
              << produto.getPreco()
              << " | quantidade: " << produto.getQuantidade();
}

void Interface::cortarFim(std::string &texto) const {
    std::string::size_type fim = texto.find_last_not_of(" \t");
    if (fim == std::string::npos) {
        texto.clear();
    } else {
        texto.erase(fim + 1);
    }
}

void Interface::executar() {
    std::string linha;

    // Um comando por linha (regra da DESCRICAO.md)
    while (std::getline(std::cin, linha)) {
        std::istringstream iss(linha);
        std::string comando;

        if (!(iss >> comando)) {
            continue; // linha vazia ou só espaços
        }

        if (comando == "-h" || comando == "--help") {
            mostrarAjuda();
            continue;
        }
        if (comando == "FIM") {
            break;
        }

        if (comando == "CRIAR_SECAO") {
            std::string nome;
            std::string extra;
            if (!(iss >> nome)) {
                std::cout << "Erro: CRIAR_SECAO espera 1 argumento:"
                          << " nome-da-secao." << std::endl;
            } else if (iss >> extra) {
                std::cout << "Erro: CRIAR_SECAO espera so 1 argumento, mas"
                          << " sobrou: " << extra
                          << " (a secao e uma palavra so)." << std::endl;
            } else {
                Status status = m_estoque.criarSecao(nome);
                if (status == OK) {
                    std::cout << "Secao criada: " << nome << std::endl;
                } else {
                    mostrarStatus(status, nome);
                }
            }
        } else if (comando == "ADD_PRODUTO") {
            std::string precoTexto;
            std::string qntTexto;
            std::string secao;
            std::string nome;

            if (!(iss >> precoTexto >> qntTexto >> secao)) {
                std::cout << "Erro: ADD_PRODUTO espera 4 argumentos: preco"
                          << " quantidade secao nome-do-produto." << std::endl;
                continue;
            }

            // O nome vem no fim da linha: o getline junta tudo em um campo só,
            // então "Cafe - Kimimo" não se quebra em três (decisão 17)
            std::getline(iss >> std::ws, nome);
            cortarFim(nome);
            if (nome.empty()) {
                std::cout << "Erro: ADD_PRODUTO espera 4 argumentos: preco"
                          << " quantidade secao nome-do-produto." << std::endl;
                continue;
            }

            double preco;
            int quantidade;
            if (!paraPreco(precoTexto, preco)) {
                std::cout << "Erro: preco invalido: " << precoTexto
                          << std::endl;
                continue;
            }
            if (!paraInteiro(qntTexto, quantidade)) {
                std::cout << "Erro: quantidade invalida: " << qntTexto
                          << std::endl;
                continue;
            }

            Produto produto(nome, quantidade, preco);
            Status status = m_estoque.adicionarProduto(produto, secao);
            if (status == OK) {
                std::cout << "Produto adicionado: " << nome << " (secao "
                          << secao << ")" << std::endl;
            } else if (status == ARGUMENTO_INVALIDO) {
                std::cout << "Erro: o nome do produto deve estar no formato"
                          << " \"nome - marca\"." << std::endl;
            } else if (status == SECAO_INEXISTENTE) {
                mostrarStatus(status, secao);
            } else {
                mostrarStatus(status, nome);
            }
        } else if (comando == "MOD_PRECO") {
            std::string precoTexto;
            std::string secao;
            std::string nome;

            if (!(iss >> precoTexto >> secao)) {
                std::cout << "Erro: MOD_PRECO espera 3 argumentos: preco"
                          << " secao nome-do-produto." << std::endl;
                continue;
            }

            std::getline(iss >> std::ws, nome);
            cortarFim(nome);
            if (nome.empty()) {
                std::cout << "Erro: MOD_PRECO espera 3 argumentos: preco"
                          << " secao nome-do-produto." << std::endl;
                continue;
            }

            double preco;
            if (!paraPreco(precoTexto, preco)) {
                std::cout << "Erro: preco invalido: " << precoTexto
                          << std::endl;
                continue;
            }

            Status status = m_estoque.modificarPreco(nome, preco, secao);
            if (status == OK) {
                std::cout << "Preco atualizado: " << nome << std::endl;
            } else if (status == SECAO_INEXISTENTE) {
                mostrarStatus(status, secao);
            } else {
                mostrarStatus(status, nome);
            }
        } else if (comando == "MOD_QNT") {
            std::string qntTexto;
            std::string secao;
            std::string nome;

            if (!(iss >> qntTexto >> secao)) {
                std::cout << "Erro: MOD_QNT espera 3 argumentos: quantidade"
                          << " secao nome-do-produto." << std::endl;
                continue;
            }

            std::getline(iss >> std::ws, nome);
            cortarFim(nome);
            if (nome.empty()) {
                std::cout << "Erro: MOD_QNT espera 3 argumentos: quantidade"
                          << " secao nome-do-produto." << std::endl;
                continue;
            }

            int quantidade;
            if (!paraInteiro(qntTexto, quantidade)) {
                std::cout << "Erro: quantidade invalida: " << qntTexto
                          << std::endl;
                continue;
            }

            Status status = m_estoque.modificarQuantidade(nome, quantidade, secao);
            if (status == OK) {
                std::cout << "Quantidade atualizada: " << nome << std::endl;
            } else if (status == SECAO_INEXISTENTE) {
                mostrarStatus(status, secao);
            } else {
                mostrarStatus(status, nome);
            }
        } else if (comando == "REM_PROD") {
            std::string secao;
            std::string nome;

            if (!(iss >> secao)) {
                std::cout << "Erro: REM_PROD espera 2 argumentos: secao"
                          << " nome-do-produto." << std::endl;
                continue;
            }

            std::getline(iss >> std::ws, nome);
            cortarFim(nome);
            if (nome.empty()) {
                std::cout << "Erro: REM_PROD espera 2 argumentos: secao"
                          << " nome-do-produto." << std::endl;
                continue;
            }

            Status status = m_estoque.removerProduto(nome, secao);
            if (status == OK) {
                std::cout << "Produto removido: " << nome << std::endl;
            } else if (status == SECAO_INEXISTENTE) {
                mostrarStatus(status, secao);
            } else {
                mostrarStatus(status, nome);
            }
        } else if (comando == "BUSCAR_PROD") {
            std::string secao;
            std::string nome;

            if (!(iss >> secao)) {
                std::cout << "Erro: BUSCAR_PROD espera 2 argumentos: secao"
                          << " nome-do-produto." << std::endl;
                continue;
            }

            std::getline(iss >> std::ws, nome);
            cortarFim(nome);
            if (nome.empty()) {
                std::cout << "Erro: BUSCAR_PROD espera 2 argumentos: secao"
                          << " nome-do-produto." << std::endl;
                continue;
            }

            std::vector<Produto> resultados;
            Status status = m_estoque.buscarProduto(nome, secao, resultados);
            if (status == SECAO_INEXISTENTE) {
                mostrarStatus(status, secao);
            } else if (status == PRODUTO_INEXISTENTE) {
                mostrarStatus(status, nome);
            } else {
                // Um resultado por linha, em ordem alfabética (a do set)
                std::vector<Produto>::const_iterator it;
                for (it = resultados.begin(); it != resultados.end(); ++it) {
                    mostrarProduto(*it);
                    std::cout << " | secao: " << secao << std::endl;
                }
            }
        } else if (comando == "ESTOQUE") {
            std::string extra;
            if (iss >> extra) {
                std::cout << "Erro: ESTOQUE nao recebe argumentos, mas"
                          << " sobrou: " << extra << std::endl;
                continue;
            }

            // vazio() quer dizer nenhuma seção criada (decisão 12)
            if (m_estoque.vazio()) {
                std::cout << "Estoque vazio." << std::endl;
                continue;
            }

            // O map entrega as seções em ordem alfabética
            std::map<std::string, Secao>::const_iterator itSecao;
            for (itSecao = m_estoque.getSecoes().begin();
                 itSecao != m_estoque.getSecoes().end(); ++itSecao) {
                std::cout << itSecao->second.getNome() << ":" << std::endl;

                // Seção vazia fica só com o cabeçalho (decisão 12)
                const std::set<Produto> &produtos =
                    itSecao->second.getProdutos();
                std::set<Produto>::const_iterator itProduto;
                for (itProduto = produtos.begin();
                     itProduto != produtos.end(); ++itProduto) {
                    mostrarProduto(*itProduto);
                    std::cout << std::endl;
                }
            }
        } else {
            std::cout << "Comando invalido: " << linha << std::endl;
        }
    }
}
