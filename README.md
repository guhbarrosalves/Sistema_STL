# Nome do sistema

Atividade da Unidade 2 de Linguagem de Programação I. Leia `ENUNCIADO.md`
antes de começar.

Uma frase dizendo o que o sistema faz. A descrição completa está em
`DESCRICAO.md`.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        o plano feito com a IA (criado na etapa 3)
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

Se o comando mudar, atualize esta seção. Na correção eu vou usar o que
estiver escrito aqui.

## Onde uso a STL

Escreva esta seção sem IA. Para cada container ou algoritmo da STL que o
sistema usa: em que classe ele está, o que guarda, e por que você escolheu
ele e não outro.

| Onde | O quê | Por quê |
| Secao | set do tipo produtos que guarda o mesmo. | Usei set para organizar a questão dos produtos por não permitir duplicatas e pela complexidade da busca |
| Estoque | map - chave é o nome da seção e o valor é o set dos produtos que estão na seção correspondente | Usei map no estoque para organizar as seções e os produtos para que se relacionassem de maneira direta - chave/valor |

## Como usei a IA

Escreva com as suas palavras:

- Modelo usado: Big Pickle
- Um pedido que deu certo, e por que você acha que deu certo: Todo o restante deu certo, acredito que porque sempre perguntava sobre as ambiguidades e coisas faltantes para corrigir e tornar a descrição mais clara.
- Um pedido que deu errado, o que veio errado e como você mudou o pedido: Como eu gostaria que funcionasse a interface. Ele veio querendo criar métodos de tokenização, mas como não conseguia compreender muito bem, pedi que ele fizesse semelhante ao projeto da agência espacial.
- Uma coisa que a IA sugeriu e você recusou, e por quê: Caso o usuário não desse nome para a seção, aceitasse como argumento válido. Não aceitei porque não há sentido uma seção não ter nome.
