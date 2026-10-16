#include "Interface.hpp"

#include <iostream>
#include <sstream>
#include <string>

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
        } else {
            std::cout << "Comando invalido: " << linha << std::endl;
        }
    }
}
