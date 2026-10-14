#ifndef STATUS_HPP
#define STATUS_HPP

enum Status {
    OK,
    SECAO_EXISTENTE,     // tentou criar seção que já existe
    SECAO_INEXISTENTE,   // seção informada não existe
    PRODUTO_EXISTENTE,   // já existe produto com esse nome na seção
    PRODUTO_INEXISTENTE, // produto não encontrado
    VALOR_INVALIDO,      // quantidade/preço <= 0
    VALOR_IGUAL,         // mesmo preço ou mesma quantidade
    ARGUMENTO_INVALIDO   // nome sem " - " ou número malformado
};

#endif
