# Descrição do sistema
## Nome e ideia

A minha ideia é fazer um estoque que possui seções e produtos.

## O que o sistema guarda

Cada produto possui um nome (formatação: nome - marca) (string), uma quantidade (inteiro positivo) e um preço (double positivo com duas casas decimais).
O nome do produto é formatado dessa forma: nome - marca. Ex: Café - Kimimo.
Cada seção possui um set de produtos.
Cada estoque possui um map com chave/valor sendo a chave a seção e o valor, um set dos produtos.

## O que dá para fazer

Terá uma interface de auxílio, que aparece quando o usuário digita "-h" ou "--help".
Essa interface de apoio servirá para mostrar como se deve mostrar todos os comandos, a estrutura deles, como os argumentos devem ser passados, o nome das funções, etc...
O estoque poderá adicionar novos produtos, adicioná-los em alguma seção já criada e removê-los.

Na interface que o usuário terá acesso, ele fará tudo o que deve fazer através de comandos, que serão listados no menu de ajuda como:

Criar seção: Recebe o nome da seção e a cria. Caso a seção já exista, retorna uma mensagem dizendo isso.
Adicionar produto: Recebe o preço do produto, a quantidade, a seção em que ele será adicionado e o nome do produto, com (nome - marca). Caso o produto já exista na mesma seção, exibe uma mensagem dizendo isso. Caso a seção não exista, retorna uma mensagem dizendo isso e não adiciona o produto ao estoque.

Modificar preço: Recebe o novo preço, a seção em que o produto está e o nome, com (nome - marca). Caso o produto não exista, exibe uma mensagem dizendo isso. O preço não pode ser o mesmo - retorna uma mensagem dizendo que se está colocando o mesmo preço no produto e mantém o antigo.

Modificar quantidade: Recebe a nova quantidade, a seção em que o produto está e o nome, com (nome - marca). Caso o produto não exista, exibe uma mensagem dizendo isso. A quantidade não pode ser a mesma - retorna uma mensagem dizendo que se está colocando a mesma quantidade no produto e mantém o antigo.

Remover produto: Recebe a seção, o nome do produto e o exclui ele do set. Caso o produto não exista, exibe uma mensagem dizendo isso.

Buscar produto: Recebe a seção em que o produto está e o nome. Caso o produto não exista, exibe uma mensagem dizendo isso.
Nesse último comando em específico, se o usuário digitar só o nome, sem o separador " - ", o sistema varre o set daquela seção e compara o trecho antes do " - " de cada produto, exibindo todos os que tiverem esse nome, mostrando nome completo, preço, quantidade e seção. 

Ao mesmo tempo, há também um comando para exibir todo o estoque, exibindo os produtos por seção.
Caso nada tenha sido criado, exibe uma mensagem de que o estoque está vazio.
Ele entra em todas as seções e imprime:
Nome da seção:
Produtos

Comando FIM: Ao digitar esse comando, o usuário encerra o programa.
Caso o usuário digite um comando inválido, faltando ou sobrando argumentos, retorna, respectivamente, uma mensagem dizendo que o comando é inválido ou que um dos argumentos está errado. 

## Regras

Nenhum produto pode ser criado sem ser adicionado em alguma seção.
As seções são definidas apenas com um nome, não podendo haver seções com nome composto, como "Limpeza e Higiene". Só pode haver a seção "Limpeza" ou "Higiene".
Caso seja criado um produto com mesmo nome e marca, uma mensagem deve ser retornada dizendo que o produto já existe na seção e que apenas o preço e quantidade podem ser alterados.
Os dados ficam apenas na memória.
As informações que são strings, são passadas normalmente, sem aspas. O nome do produto é sempre o último argumento da linha, por isso pode conter espaços.
Caso o usuário digite algum valor negativo ou zero, retorna uma mensagem dizendo isso e não faz nada, ou seja, não realiza a operação.
O operador < para a ordenação do set será definido pela ordem alfabética, ou seja, compara o nome completo e ordena os produtos, sendo também sensível a maiúsculas.
Cada método devolve um status/mensagem e a interface decide o que imprimir.
A interface lê um comando por linha, exibindo a saída correspondente até encontrar o comando FIM.

## Quando algo dá errado

Retorna uma mensagem explicando a situação baseada na seção 'Regras' e não executa a ação.

## Classes que eu imagino

A minha ideia é fazer um estoque que possui seções e produtos.
Com isso, criamos 3 classes: uma classe de produto, outra de seções e outra do estoque.

Cada produto possui um nome (com a marca descrita no nome), uma quantidade e um preço.
Cada seção possui um set de produtos.
Cada estoque possui um map com chave/valor sendo seção/set de produtos.

## Exemplo de uso
Esqueleto dos comandos:

CRIAR_SECAO secao
ADD_PRODUTO preco quantidade secao nome - marca
MOD_PRECO novo_preco secao nome - marca
MOD_QNT nova_qnt secao nome - marca
REM_PROD secao nome - marca
BUSCAR_PROD secao nome
ESTOQUE // Exibe todo o estoque
FIM //encerra a inserção no estoque
