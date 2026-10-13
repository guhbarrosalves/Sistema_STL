# Plano de implementação

Sistema: um estoque com seções e produtos. Nada foi escrito em código ainda;
este plano só descreve o que será feito. A fonte da verdade é o
`DESCRICAO.md`.

## 1. Visão geral

A lógica fica em três classes (`Produto`, `Secao`, `Estoque`) que **não usam
`cin` nem `cout`**: elas recebem dados por parâmetro e devolvem um status.
Toda leitura de teclado e toda escrita na tela ficam na `Interface`.

Os métodos devolvem um `enum Status` (ver 3.0), e a `Interface` traduz cada
status em uma mensagem. Assim a regra fica separada da tela (prática 5.5).

## 2. Arquivos

```text
include/Status.hpp      enum de status (sem .cpp)
include/Produto.hpp     classe Produto
src/Produto.cpp
include/Secao.hpp       classe Secao
src/Secao.cpp
include/Estoque.hpp     classe Estoque
src/Estoque.cpp
include/Interface.hpp   menu, leitura e escrita
src/Interface.cpp
src/main.cpp            cria o Estoque e chama a Interface
exemplos/cenario1.txt   entradas para testar
exemplos/cenario2.txt
exemplos/cenario3.txt
```

O comando do `README.md` (`g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude
-o sistema`) já cobre esses arquivos.

## 3. Classes

### 3.0 `enum Status` (em `Status.hpp`)

```cpp
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
```

Uso um `enum` simples (não `enum class`) porque é o que já foi visto.

### 3.1 `Produto`

Guarda:
- `std::string nome` no formato `"nome - marca"` (ex.: `"Cafe - Kimimo"`);
- `int quantidade` (positivo);
- `double preco` (positivo).

Métodos:
- construtor;
- `nome()`, `quantidade()`, `preco()`;
- `setQuantidade(int)`, `setPreco(double)`;
- `operator<` — compara **só o `nome`**, ordem alfabética, sensível a
  maiúsculas/minúsculas (é o `<` do `std::string`);
- `operator==` — `nome` iguais.

Observação: o `set` manterá os produtos ordenados por esse `operator<` e
sem repetidos, que é exatamente a regra da descrição.

### 3.2 `Secao`

Guarda:
- `std::string nome`;
- `std::set<Produto> produtos`.

Métodos (os que alteram devolvem `Status`):
- `nome()`;
- `adicionar(Produto)` — `PRODUTO_EXISTENTE` se o nome já está no set;
- `remover(nome)`;
- `modificarPreco(nome, novoPreco)`;
- `modificarQuantidade(nome, novaQnt)`;
- `buscar(nome, std::vector<Produto>& saida)` — se `nome` tem `" - "`, busca
  exata; senão, busca parcial pelo trecho antes de `" - "`;
- `vazia()`;
- `produtos()`.

Detalhe: como o elemento de um `set` é `const`, para alterar preço/quantidade
eu localizo o produto, guardo os dados, removo (`erase`) e insiro de novo com
o valor novo.

### 3.3 `Estoque`

Guarda:
- `std::map<std::string, Secao> secoes` — chave é o nome da seção.

Métodos:
- `criarSecao(nome)`;
- `adicionarProduto(Produto, secao)`;
- `removerProduto(nome, secao)`;
- `modificarPreco(nome, novoPreco, secao)`;
- `modificarQuantidade(nome, novaQnt, secao)`;
- `buscarProduto(nome, secao, std::vector<Produto>& saida)`;
- `vazio()` / `secoes()`.

### 3.4 `Interface`

Não é uma classe "de dados": lê linha a linha do `cin`, quebra em tokens
respeitando as aspas, chama o método certo do `Estoque` e imprime a mensagem
correspondente ao `Status`. Também trata `-h`/`--help`, `FIM`, comando
inválido e número de argumentos errado.

## 4. Onde uso a STL e por quê

| Lugar | Container/algoritmo | Por quê |
| --- | --- | --- |
| `Secao` | `std::set<Produto>` | Mantém os produtos **ordenados** pelo `operator<` e **sem repetidos**; um produto com mesmo nome/marca não entra duas vezes. `set` já resolve ordem + unicidade. |
| `Estoque` | `std::map<std::string, Secao>` | Associa o nome da seção ao seu conteúdo, acha a seção pelo nome, e já entrega as seções em ordem alfabética na hora de exibir. |
| `Secao::buscar` | `std::find` (algorithm) | Busca exata usando `operator==` de `Produto`, como no exemplo da aula. |
| `Secao` (interno) | `std::set::find` | Checar duplicado e localizar produto pelo `operator<`. |
| Retornos de busca | `std::vector<Produto>` | A busca parcial devolve nenhum, um ou vários; `vector` é a coleção de tamanho variável mais simples. |
| Nomes | `std::string` | Texto padrão. |

Observação didática: `set::find` é O(log n); `std::find` varre tudo, O(n).
Uso o `std::find` no método de busca para cumprir o requisito do enunciado.

## 5. Decisões já confirmadas com o estudante

1. Valor do `map` é um objeto `Secao` (`map<string, Secao>`), e a `Secao`
   guarda o `set<Produto>`. Mantém as três classes com papel claro.
2. `ADD_PRODUTO` exige o nome no formato `"nome - marca"`. Nome sem `" - "`
   devolve `ARGUMENTO_INVALIDO`. O nome sozinho só é aceito na busca.
3. `operator<` compara só o `nome` completo (`"nome - marca"`), sensível a
   maiúsculas.
4. Seção informada e não existente devolve `SECAO_INEXISTENTE`.
5. Quantidade/preço iguais devolvem `VALOR_IGUAL`; valores <= 0 devolvem
   `VALOR_INVALIDO`.

## 6. Etapas

Cada etapa termina compilando com o comando do `README.md` e testável.

- **Etapa 1 — Estrutura + `Produto`.** Cria `include/`, `src/`, `exemplos/`;
  `Status.hpp`; `Produto.hpp/.cpp` com `operator<` e `operator==`; `main.cpp`
  com um teste temporário que cria dois produtos e compara.
  Teste: `g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema && ./sistema`.

- **Etapa 2 — `Secao`.** Cria `Secao.hpp/.cpp` (`set<Produto>` e os métodos de
  adicionar/remover/modificar/buscar devolvendo `Status`). Ajusta o `main.cpp`
  para testar direto.

- **Etapa 3 — `Estoque`.** Cria `Estoque.hpp/.cpp` (`map<string, Secao>`) com
  todos os métodos. Ajusta o `main.cpp` para um teste direto.

- **Etapa 4 — `Interface`: `FIM`, ajuda e comando inválido.** Cria
  `Interface.hpp/.cpp` lendo linhas; trata `-h`/`--help`, `FIM` e comando
  desconhecido. `main.cpp` passa a criar `Estoque` e chamar a `Interface`.
  Teste: `printf 'FIM\n' | ./sistema`.

- **Etapa 5 — `CRIAR_SECAO` e `ADD_PRODUTO`.** Tokenizador que respeita aspas;
  tratamento de argumentos faltando e número inválido.
  Teste: `./sistema < exemplos/cenario1.txt`.

- **Etapa 6 — `MOD_PRECO`, `MOD_QNT`, `REM_PROD`.** Inclui os casos
  `VALOR_IGUAL`, `VALOR_INVALIDO`, `PRODUTO_INEXISTENTE`.
  Teste: `./sistema < exemplos/cenario2.txt`.

- **Etapa 7 — `BUSCAR_PROD` e `ESTOQUE`.** Busca exata com `std::find`, busca
  parcial por prefixo, e exibição completa por seção.
  Teste: `./sistema < exemplos/cenario3.txt`.

- **Etapa 8 — Fechamento.** Cria/afina os `exemplos/`, roda todos e confere os
  resultados. Preenche no `README.md` só a coluna que cabe à IA (as seções
  "Onde uso a STL" e "Como usei a IA" ficam por conta do estudante).

## 7. Fora do escopo

Não vou acrescentar menu numerado, persistência em arquivo, ordenar por preço,
nem busca global. Só o que está na `DESCRICAO.md`.
