#include "Interface.hpp"

#include <iostream>
#include <string>

Interface::Interface(Estoque &estoque) : m_estoque(estoque) {}

void Interface::mostrarAjuda() const {
    std::cout << "Comandos disponiveis:" << std::endl;
    std::cout << " CRIAR_SECAO \"nome da secao\"" << std::endl;
    std::cout << " ADD_PRODUTO \"nome - marca\" preco quantidade \"secao\""
              << std::endl;
    std::cout << " MOD_PRECO \"nome - marca\" novo_preco \"secao\"" << std::endl;
    std::cout << " MOD_QNT \"nome - marca\" nova_quantidade \"secao\""
              << std::endl;
    std::cout << " REM_PROD \"nome - marca\" \"secao\"" << std::endl;
    std::cout << " BUSCAR_PROD \"nome\" \"secao\"" << std::endl;
    std::cout << " ESTOQUE" << std::endl;
    std::cout << " FIM" << std::endl;
    std::cout << " -h, --help   mostra esta ajuda" << std::endl;
}

void Interface::executar() {
    std::string linha;
    while (std::getline(std::cin, linha)) {
        std::string::size_type inicio = linha.find_first_not_of(" \t\r");
        if (inicio == std::string::npos) {
            continue;
        }
        std::string::size_type fim = linha.find_last_not_of(" \t\r");
        std::string comando = linha.substr(inicio, fim - inicio + 1);

        if (comando == "-h" || comando == "--help") {
            mostrarAjuda();
        } else if (comando == "FIM") {
            break;
        } else {
            std::cout << "Comando invalido: " << comando << std::endl;
        }
    }
}
