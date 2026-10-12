# Descrição do sistema

Escreva este arquivo sem IA, antes de qualquer código. Apague as instruções
em itálico quando preencher.

## Nome e ideia

A minha ideia é fazer um estoque que possui sessões e produtos.

## O que o sistema guarda

Cada produto possui um nome (com a marca descrita no nome), uma quantidade e um preço.
Cada sessão possui um set de produtos.
Cada mercado possui um map com chave/valor sendo sessão/produto.

## O que dá para fazer

Tera uma interface de auxílio, que aparece quando o usuário digita "-h" ou "--help".
O mercado poderá adicionar novos produtos, adicioná-los em alguma sessão já criada e removê-los do estoque, caso tenham sido vendidos.

Na interface que o usuário terá acesso, ele fará tudo o que deve fazer através de comandos, que serão listados no menu de ajuda, como criar sessão, adicionar produto, modificar preço, modificar quantidade, remover produto, buscar produto.

Ao mesmo tempo, há também um comando para exibir todo o estoque, exibindo os produtos por sessão.

## Regras

 Caso alguma sessão não exista, retorna uma mensagem dizendo isso e não adiciona o produto ao estoque.

Como as estruturas de dados usadas não permitem duplicatas, o usuário não conseguirá criar duas vezes o mesmo produto, apenas conseguirá alterar a quantidade e seu preço. Apesar disso, caso seja criado um produto com o mesmo nome, uma mensagem deve ser retornada dizendo que o produto já existe e que apenas o preço e quantidade podem ser alterados.

## Quando algo dá errado

Como as estruturas de dados usadas não permitem duplicatas, o usuário não conseguirá criar duas vezes o mesmo produto, apenas conseguirá alterar a quantidade e seu preço.

Quando um produto é buscado e não encontrado, ou é adicionado em uma sessão que não existe, uma mensagem é retornada no terminal dizendo que o produto não foi encontrado ou que a sessão não existe, mostrando em seguida o comando para adicioná-lo ou criá-lo.

## Classes que eu imagino

A minha ideia é fazer um estoque que possui sessões e produtos.
Com isso, criamos 3 classes: uma classe de produto, outra de sessões e outra do mercado.

Cada produto possui um nome (com a marca descrita no nome), uma quantidade e um preço.
Cada sessão possui um set de produtos.
Cada mercado possui um map com chave/valor sendo sessão/produto.

## Exemplo de uso

CRIAR_SESSAO Alimentos
ADD_PRODUTO Café - Kimimo 5.99 10 Alimentos
ESTOQUE // Exibe todo o estoque
