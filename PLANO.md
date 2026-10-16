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
- `getNome()`, `getQuantidade()`, `getPreco()`;
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
- `getNome()`;
- `adicionar(Produto)` — `PRODUTO_EXISTENTE` se o nome já está no set;
- `remover(nome)`;
- `modificarPreco(nome, novoPreco)`;
- `modificarQuantidade(nome, novaQnt)`;
- `buscar(nome, std::vector<Produto>& saida)` — se `nome` tem `" - "`, busca
  exata; senão, busca parcial pelo trecho antes de `" - "`;
- `vazia()`;
- `getProdutos()`.

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
- `vazio()` / `getSecoes()`.

### 3.4 `Interface`

Não é uma classe "de dados": lê uma linha por vez com `getline`, parseia a
linha com `std::istringstream` (`>>` para cada campo de uma palavra;
`getline(iss >> ws, ...)` para o nome do produto, que vem no fim e pode ter
espaços), chama o método certo do `Estoque` e imprime a mensagem
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
| Leitura da linha | `std::istringstream` + `getline` | `>>` separa os campos de uma palavra; `getline` pega o nome do produto (com espaços) como o resto da linha. |
| Nomes | `std::string` | Texto padrão. |

Observação didática: `set::find` é O(log n); `std::find` varre tudo, O(n).
Uso o `std::find` no método de busca para cumprir o requisito do enunciado.

## 5. Decisões já confirmadas com o estudante

1. Valor do `map` é um objeto `Secao` (`map<string, Secao>`), e a `Secao`
   guarda o `set<Produto>`. Mantém as três classes com papel claro.
2. `ADD_PRODUTO` exige o nome no formato `"nome - marca"` (sem aspas na
   linha). O nome do produto é sempre o **último campo da linha**, lido com
   `getline` — assim ele pode conter espaços. Nome sem `" - "` devolve
   `ARGUMENTO_INVALIDO`. O nome sozinho só é aceito na busca.
3. `operator<` compara só o `nome` completo (`"nome - marca"`), sensível a
   maiúsculas.
4. Seção informada e não existente devolve `SECAO_INEXISTENTE`.
5. Quantidade/preço iguais devolvem `VALOR_IGUAL`; valores <= 0 devolvem
   `VALOR_INVALIDO`.
6. `Secao::adicionar` valida na ordem: formato do nome sem `" - "` →
   `ARGUMENTO_INVALIDO`; quantidade/preço <= 0 → `VALOR_INVALIDO`; produto
   repetido → `PRODUTO_EXISTENTE`.
7. `modificarPreco`/`modificarQuantidade` validam na ordem: produto não
   existe → `PRODUTO_INEXISTENTE`; valor <= 0 → `VALOR_INVALIDO`; valor igual
   ao atual → `VALOR_IGUAL`.
8. `buscar` devolve `PRODUTO_INEXISTENTE` quando nada é encontrado (o vetor
   sai vazio); `OK` quando acha um ou mais.
9. Busca parcial (nome sem `" - "`) compara o prefixo de cada produto com
   igualdade exata: `"Cafe"` acha `"Cafe - Kimimo"`, mas não acha
   `"Cafezinho - Kimimo"`.
10. Nos métodos do `Estoque` que recebem seção, a seção é conferida **primeiro**:
    se não existe → `SECAO_INEXISTENTE`, sem olhar o produto. Ex.: produto com
    nome sem `" - "` e valor 0 em seção inexistente devolve `SECAO_INEXISTENTE`.
11. `criarSecao` com nome vazio (`""`) devolve `ARGUMENTO_INVALIDO`; nome
    repetido devolve `SECAO_EXISTENTE`.
12. `Estoque::vazio()` significa **nenhuma seção criada** (`secoes.empty()`).
    Seção criada mas sem produtos continua aparecendo na exibição do estoque,
    com o nome da seção e nenhum produto abaixo.
13. As validações da `Interface` (número malformado, quantidade de
    argumentos) acontecem **antes** do `Estoque` ser chamado. Ex.:
    `ADD_PRODUTO abc 2 SecaoInexistente A - B` devolve erro de número, não
    `SECAO_INEXISTENTE`.
14. Ordem de validação da `ADD_PRODUTO`: (a) número malformado ou quantidade
    de argumentos errada (inclusive o nome faltando) → a `Interface` mostra o
    erro sem chamar o `Estoque`; (b) seção inexistente → `SECAO_INEXISTENTE`;
    (c) nome sem `" - "` → `ARGUMENTO_INVALIDO`; (d) preço/quantidade ≤ 0 →
    `VALOR_INVALIDO`; (e) produto repetido → `PRODUTO_EXISTENTE`.
15. Nenhum argumento vai entre aspas; tudo é separado apenas por espaço.
16. O nome de seção é **uma única palavra** (sem espaços). Palavra a mais no
    `CRIAR_SECAO` → a `Interface` mostra erro de argumento sem chamar o
    `Estoque`.
17. Ordem dos campos na linha: vêm primeiro os valores, depois a seção e por
    último o nome do produto. Ex.: `ADD_PRODUTO preco quantidade secao
    nome - marca`. O nome do produto é lido com `getline(iss >> ws, ...)`,
    que considera o resto da linha um campo só.

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
  todos os métodos. Em cada método que recebe seção: acha a seção com o
  `find` do `map` e, se não achar, `SECAO_INEXISTENTE` (decisão 10); achando,
  delega para a `Secao` e devolve o status dela. `criarSecao` confere nome
  vazio (decisão 11) e seção repetida, e usa `insert` — nunca `operator[]`,
  porque ele criaria uma `Secao` vazia e `Secao` não tem construtor padrão.
  `vazio()`/`getSecoes()` conforme a decisão 12. Ajusta o `main.cpp` para um
  teste direto: cria seções, adiciona produtos, exercita cada status novo
  (`SECAO_EXISTENTE`, `SECAO_INEXISTENTE`) e imprime o `map` por inteiro.

- **Etapa 4 — `Interface`: `FIM`, ajuda e comando inválido.** Cria
  `Interface.hpp/.cpp` lendo linhas; trata `-h`/`--help`, `FIM` e comando
  desconhecido. `main.cpp` passa a criar `Estoque` e chamar a `Interface`.
  Teste: `printf 'FIM\n' | ./sistema`.

- **Etapa 5 — `CRIAR_SECAO` e `ADD_PRODUTO`.** Leitura da linha com
  `getline` + `istringstream` (`>>` para os campos, `getline` para o nome no
  fim); tratamento de argumentos faltando/sobrando e número inválido.
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
